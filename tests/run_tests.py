#!/usr/bin/env python3
"""Automated tests for ft_select.

Runs ft_select inside a real interactive bash, in a pseudo-terminal,
types keys and sends signals like an evaluator would, then checks the
output, the terminal settings (stty -g) and, if available, valgrind
and norminette.

Usage:  python3 tests/run_tests.py        (only failures + summary)
        python3 tests/run_tests.py -v     (every test)
"""
import fcntl
import os
import pty
import re
import select
import shutil
import signal
import struct
import subprocess
import sys
import termios
import time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BIN = os.path.join(ROOT, "ft_select")
VERBOSE = "-v" in sys.argv
MARK = "FTSELECT_PROMPT>"
TERM = "xterm-256color"

G, R, Y, B, N = "\033[32m", "\033[31m", "\033[33m", "\033[1m", "\033[0m"
results = []
section_name = ""


# --------------------------------------------------------------- helpers

def section(name):
    global section_name
    section_name = name
    if VERBOSE:
        print(f"\n{B}{name}{N}")


def check(name, ok, detail=""):
    results.append((section_name, name, ok, detail))
    if VERBOSE or not ok:
        tag = f"{G}PASS{N}" if ok else f"{R}FAIL{N}"
        where = "" if VERBOSE else f"[{section_name}] "
        line = f"  {tag} {where}{name}"
        if detail and not ok:
            line += f"\n       -> {detail}"
        print(line)


def skip(name, why):
    results.append((section_name, name, None, why))
    print(f"  {Y}SKIP{N} [{section_name}] {name}\n       -> {why}")


def clean(data):
    s = data.decode(errors="replace")
    s = re.sub(r"\x1b\[[0-9;?]*[A-Za-z]", "", s)
    s = re.sub(r"\x1b[()][0-9A-B]", "", s)
    return re.sub(r"\x1b[=>78]", "", s)


def vis(data):
    return data.decode(errors="replace").replace("\x1b", "^[")


class Shell:
    """An interactive bash running in a pseudo-terminal."""

    def __init__(self, rows=24, cols=80, term=TERM):
        self.pid, self.fd = pty.fork()
        if self.pid == 0:
            os.closerange(3, 4096)
            os.chdir(ROOT)
            env = {"PATH": os.environ.get("PATH", "/usr/bin:/bin"),
                   "TERM": term, "PS1": MARK, "HOME": os.environ.get("HOME", "/tmp"),
                   "LANG": "C"}
            os.execve("/bin/bash", ["bash", "--norc", "--noprofile", "-i"], env)
        self.resize(rows, cols)
        self.prompt(5)
        self.ref = self.stty()

    def resize(self, rows, cols):
        fcntl.ioctl(self.fd, termios.TIOCSWINSZ,
                    struct.pack("HHHH", rows, cols, 0, 0))

    def read(self, t=0.4):
        out, end = b"", time.time() + t
        while time.time() < end:
            r, _, _ = select.select([self.fd], [], [], 0.05)
            if r:
                try:
                    d = os.read(self.fd, 65536)
                except OSError:
                    break
                if not d:
                    break
                out += d
        return out

    def prompt(self, t=4):
        out, end = b"", time.time() + t
        while time.time() < end:
            out += self.read(0.1)
            if out.rstrip().endswith(MARK.encode()):
                break
        return out

    def run(self, cmd, t=4):
        os.write(self.fd, cmd.encode() + b"\n")
        return self.prompt(t)

    def start(self, cmd, t=0.8):
        os.write(self.fd, cmd.encode() + b"\n")
        return self.read(t)

    def key(self, k, t=0.3):
        os.write(self.fd, k if isinstance(k, bytes) else k.encode())
        return self.read(t)

    def keys(self, seq, t=0.3):
        out = b""
        for k in seq:
            out += self.key(k, t)
        return out

    def stty(self):
        found = re.findall(r"([0-9a-f]+(?::[0-9a-f]+){10,})",
                           clean(self.run("stty -g")))
        return found[-1] if found else None

    def restored(self):
        return self.stty() == self.ref

    def rc(self):
        found = re.findall(r"RC\[(\d+)\]", clean(self.run('echo "RC[$?]"')))
        return int(found[-1]) if found else None

    def captured(self):
        found = re.findall(r"OUT\[([^\]$]*)\]",
                           clean(self.run('echo "OUT[$out]"')))
        return found[-1] if found else None

    def program_running(self):
        return os.tcgetpgrp(self.fd) != self.pid

    def signal_program(self, sig):
        os.killpg(os.tcgetpgrp(self.fd), sig)

    def close(self):
        try:
            os.kill(self.pid, signal.SIGKILL)
            os.waitpid(self.pid, 0)
        except OSError:
            pass
        try:
            os.close(self.fd)
        except OSError:
            pass


def select_run(sh, keys, args="a b c d"):
    """Runs out=$(./ft_select args), types keys, returns captured output."""
    sh.start(f"out=$(./ft_select {args})")
    sh.keys(keys)
    sh.prompt(4)
    return sh.captured()


UP, DOWN, RIGHT, LEFT = b"\x1b[A", b"\x1b[B", b"\x1b[C", b"\x1b[D"
ESC, BSP, DEL = b"\x1b", b"\x7f", b"\x1b[3~"


# ------------------------------------------------------------------ tests

def test_build():
    section("Build")
    p = subprocess.run(["make"], cwd=ROOT, capture_output=True, text=True)
    check("make succeeds", p.returncode == 0, p.stderr[-300:])
    p = subprocess.run(["make"], cwd=ROOT, capture_output=True, text=True)
    relinked = [l for l in p.stdout.splitlines()
                if l.startswith(("cc ", "gcc ", "clang ", "ar "))]
    check("second make does nothing (no relink)", not relinked, str(relinked[:2]))
    author = os.path.join(ROOT, "author")
    ok = os.path.isfile(author) and re.fullmatch(r"\S+\n", open(author).read())
    check("author file: one login followed by \\n", bool(ok))
    stray = [f for f in os.listdir(ROOT) if "=" in f]
    check("no stray files at repo root", not stray, f"found: {stray}")


def test_errors():
    section("Error handling")
    sh = Shell()
    cases = [
        ("no argument", "./ft_select"),
        ("only empty arguments", './ft_select "" ""'),
        ("empty environment (env -i)", "env -i ./ft_select a b"),
        ("unknown TERM", "TERM=nope ./ft_select a b"),
        ("TERM without required capabilities (dumb)", "TERM=dumb ./ft_select a b"),
        ("stdin is not a terminal", "echo hi | ./ft_select a b"),
    ]
    for name, cmd in cases:
        out = clean(sh.run(cmd))
        rc = sh.rc()
        msg = out.replace(cmd, "").replace(MARK, "").strip()
        check(f"{name}: message + exit code != 0", rc not in (None, 0) and msg != "",
              f"rc={rc} output={msg!r}")
        check(f"{name}: terminal intact", sh.restored())
    sh.close()


def test_display():
    section("Display")
    sh = Shell()
    d = vis(sh.start("./ft_select aa bb cc"))
    check("switches to alternate screen (ti)", "^[[?1049h" in d)
    check("hides the cursor (vi)", "^[[?25l" in d)
    check("cursor on first item = underlined", re.search(r"\^\[\[4maa", d) is not None)
    d = vis(sh.key(" "))
    check("space: item reversed, cursor moves to next",
          re.search(r"\^\[\[7maa", d) and re.search(r"\^\[\[4mbb", d), d[:120])
    d = vis(sh.keys([UP, UP]))
    check("up on first item wraps to last", re.search(r"\^\[\[4mcc", d) is not None)
    d = vis(sh.key(DOWN))
    check("down on last item wraps to first, selected + cursor = both",
          re.search(r"\^\[\[7m\^\[\[4maa|\^\[\[4m\^\[\[7maa", d) is not None, d[:120])
    sh.key("x")
    check("unknown key is ignored", sh.program_running())
    d = vis(sh.key(ESC) + sh.prompt(3))
    check("esc: leaves alternate screen (te)", "^[[?1049l" in d)
    check("esc: shows the cursor again (ve)", "^[[?25h" in d)
    check("esc: terminal restored", sh.restored())
    sh.close()


def test_output():
    section("Output to the shell")
    sh = Shell()
    cases = [
        ("select a and c, Enter -> 'a c'", [" ", DOWN, " ", "\n"], "a c"),
        ("select all, Enter -> 'a b c d'", [" ", " ", " ", " ", "\n"], "a b c d"),
        ("select then unselect", [" ", " ", UP, " ", "\n"], "a"),
        ("Enter with nothing selected -> nothing", ["\n"], ""),
        ("Esc after selecting -> nothing", [" ", ESC], ""),
        ("delete everything -> behaves like Esc", [" ", BSP, DEL, BSP, BSP], ""),
        ("delete b, then select next item (c)", [DOWN, BSP, " ", "\n"], "c"),
        ("delete last item -> cursor goes to first", [UP, BSP, " ", "\n"], "a"),
    ]
    for name, keys, want in cases:
        got = select_run(sh, keys)
        check(name, got == want, f"got {got!r}, expected {want!r}")
    got = select_run(sh, [" ", " ", " ", " ", "\n"], "'with space' '*' '-n' '%s%d'")
    check("special arguments returned unchanged", got == "with space * -n %s%d", repr(got))
    sh.start("./ft_select a b c > /tmp/ft_select_test_out.txt; echo RC=$?")
    out = clean(sh.keys([" ", "\n"]) + sh.prompt(4))
    content = open("/tmp/ft_select_test_out.txt").read()
    os.remove("/tmp/ft_select_test_out.txt")
    check("stdout redirected to a file: menu works, file = 'a\\n'",
          content == "a\n" and "RC=0" in out, repr(content))
    check("terminal restored", sh.restored())
    sh.close()

    sh = Shell()
    sh.run("echo HISTORY_LINE")
    sh.start("./ft_select a b c")
    sh.key(" ")
    d = vis(sh.key("\n", 1.0))
    after = d.split("^[[?1049l")[-1]
    check("result written after leaving alternate screen, then newline",
          re.search(r"a\r?\n", after) is not None, repr(after[:60]))
    check("normal screen not cleared on exit", "^[[2J" not in after)
    sh.close()


def test_layout():
    section("Columns and window size")
    sh = Shell(rows=3, cols=40)
    d = vis(sh.start("./ft_select one two three four five six seven"))
    pos = {(int(r) - 1, int(c) - 1) for r, c in re.findall(r"\^\[\[(\d+);(\d+)H", d)}
    want = {(0, 0), (1, 0), (2, 0), (0, 6), (1, 6), (2, 6), (0, 12)}
    check("7 items in a 3-line window -> 3 columns", pos == want, str(sorted(pos)))
    d = vis(sh.key(RIGHT))
    check("right arrow jumps one column", re.search(r"\^\[\[4mfour", d) is not None)
    d = vis(sh.key(LEFT))
    check("left arrow jumps back", re.search(r"\^\[\[4mone", d) is not None)
    sh.key(" ")
    sh.resize(2, 6)
    sh.signal_program(signal.SIGWINCH)
    out = clean(sh.read(0.5))
    check("window too small: message, program keeps running",
          sh.program_running() and out.strip() != "", repr(out[-40:]))
    sh.keys([DOWN, " ", RIGHT])
    check("keys while too small: no crash", sh.program_running())
    sh.resize(24, 80)
    sh.signal_program(signal.SIGWINCH)
    d = vis(sh.read(0.5))
    check("window enlarged: menu redrawn immediately, selection kept",
          re.search(r"\^\[\[7mone", d) is not None and "seven" in d)
    for rows, cols in [(1, 80), (0, 0), (1, 1)]:
        sh.resize(rows, cols)
        sh.signal_program(signal.SIGWINCH)
        sh.read(0.3)
        check(f"{rows}x{cols} window: no crash", sh.program_running())
    sh.resize(24, 80)
    sh.signal_program(signal.SIGWINCH)
    sh.key(ESC)
    sh.prompt(3)
    check("terminal restored", sh.restored())
    sh.resize(10, 20)
    sh.start("./ft_select " + "x" * 60 + " ok")
    check("item wider than the window: no crash", sh.program_running())
    sh.key(ESC)
    sh.prompt(3)
    sh.close()

    sh = Shell(rows=10, cols=50)
    sh.start("./ft_select $(seq 1 500)")
    for i in range(60):
        sh.key(RIGHT if i % 3 else DOWN, 0.02)
        sh.key(" ", 0.02)
        if i % 7 == 0:
            sh.resize(3 + i % 30, 10 + 3 * i)
            sh.signal_program(signal.SIGWINCH)
            sh.read(0.02)
        if not sh.program_running():
            break
    check("stress: 500 items, fast keys and resizes, no crash", sh.program_running())
    sh.resize(24, 80)
    sh.key("\n", 0.5)
    sh.prompt(3)
    check("stress: terminal restored", sh.restored())
    sh.close()


def test_signals():
    section("Signals")
    names = ["SIGINT", "SIGQUIT", "SIGTERM", "SIGHUP", "SIGUSR1", "SIGUSR2",
             "SIGALRM", "SIGPIPE", "SIGABRT", "SIGSEGV", "SIGBUS", "SIGFPE"]
    sh = Shell()
    for name in names:
        sh.start("./ft_select a b c")
        sh.signal_program(getattr(signal, name))
        d = vis(sh.prompt(3))
        check(f"kill -{name[3:]}: terminal + cursor restored",
              sh.restored() and "^[[?25h" in d)
        sh.run(f"stty {sh.ref}; tput rmcup; tput cnorm")
    for name, k in [("Ctrl+C", b"\x03"), ("Ctrl+\\", b"\x1c")]:
        sh.start("./ft_select a b c")
        sh.key(k)
        sh.prompt(3)
        check(f"{name}: terminal restored", sh.restored())
    sh.close()


def test_suspend():
    section("Ctrl+Z / fg")
    path = "/proc/sys/dev/tty/legacy_tiocsti"
    if os.path.exists(path) and open(path).read().strip() == "0":
        skip("Ctrl+Z / fg", "TIOCSTI is disabled on this machine "
             "(sudo sysctl -w dev.tty.legacy_tiocsti=1 to test it)")
        return
    sh = Shell()
    sh.start("./ft_select a b c")
    sh.keys([DOWN, " "])
    out = clean(sh.key(b"\x1a", 1.0))
    check("Ctrl+Z: program stopped, shell prompt back", "Stopped" in out, repr(out[-60:]))
    check("Ctrl+Z: terminal normal while stopped", sh.restored())
    check("Ctrl+Z: shell usable while stopped", "ok_typed" in clean(sh.run("echo ok_typed")))
    d = vis(sh.start("fg"))
    check("fg: menu back, selection and cursor kept",
          re.search(r"\^\[\[7mb", d) is not None and re.search(r"\^\[\[4mc", d) is not None)
    out = clean(sh.key(b"\x1a", 1.0))
    check("second Ctrl+Z also works", "Stopped" in out)
    sh.start("fg")
    sh.key(UP)
    out = clean(sh.key("\n", 0.5) + sh.prompt(3))
    check("after 2x Ctrl+Z/fg, Enter still returns the selection",
          re.search(r"(^|\n)b\r?\n", out) is not None, repr(out[-40:]))
    check("terminal restored at the end", sh.restored())
    sh.close()


def test_valgrind():
    section("Valgrind")
    if not shutil.which("valgrind"):
        skip("valgrind", "valgrind is not installed")
        return
    supp = "--suppressions=ncurses.supp" if os.path.exists(os.path.join(ROOT, "ncurses.supp")) else ""
    log = "/tmp/ft_select_vg_%s.log"
    cmd = ("valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes "
           f"{supp} --log-file={log} ./ft_select a b c d")
    cases = {
        "Enter": [" ", DOWN, " ", "\n"],
        "Esc": [" ", ESC],
        "delete everything": [BSP, BSP, DEL, BSP],
        "Ctrl+C": [b"\x03"],
    }
    sh = Shell()
    for name, keys in cases.items():
        tag = name.replace(" ", "_").replace("+", "")
        sh.start(cmd % tag, 3.0)
        sh.keys(keys, 0.6)
        sh.prompt(8)
        time.sleep(0.5)
        try:
            text = open(log % tag).read()
            os.remove(log % tag)
        except OSError:
            check(f"{name}: valgrind report", False, "no report written")
            continue
        errors = re.search(r"ERROR SUMMARY: (\d+) errors", text)
        lost = re.findall(r"(definitely|indirectly) lost: ([\d,]+) bytes", text)
        check(f"{name}: 0 memory error", errors is not None and errors.group(1) == "0")
        check(f"{name}: no leak", all(v == "0" for _, v in lost))
        own = re.findall(r"Open file descriptor \d+: (.*)\n(?!.*inherited from parent)", text)
        check(f"{name}: no file descriptor left open", not own, str(own[:3]))
    sh.close()


def test_norm():
    section("Norm")
    if not shutil.which("norminette"):
        skip("norminette", "norminette is not installed")
        return
    p = subprocess.run(["norminette", "src", "includes", "libft"], cwd=ROOT,
                       capture_output=True, text=True)
    errors = [l for l in p.stdout.splitlines() if "Error" in l]
    check("norminette: no error", not errors, "\n       -> ".join(errors[:6]))


# ------------------------------------------------------------------- main

def main():
    print(f"{B}ft_select tests{N} (about 3 minutes)")
    tests = [test_build, test_errors, test_display, test_output,
             test_layout, test_signals, test_suspend, test_valgrind, test_norm]
    for t in tests:
        if t is not test_build and not os.path.isfile(BIN):
            break
        try:
            t()
        except Exception as e:  # a crash in one section must not stop the rest
            check(f"{t.__name__} ran without exception", False, repr(e))
    passed = sum(1 for r in results if r[2] is True)
    failed = [r for r in results if r[2] is False]
    skipped = sum(1 for r in results if r[2] is None)
    print()
    summary = f"{passed} passed, {len(failed)} failed, {skipped} skipped"
    if failed:
        print(f"{R}{B}✗ {summary}{N}")
        sys.exit(1)
    print(f"{G}{B}✓ All tests passed{N} ({summary})")


if __name__ == "__main__":
    main()
