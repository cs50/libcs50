import functools
import os
import sys
import traceback


def setIO(input, expected=None):
    def to_bytes(s):
        """ Converts argument to bytes if it isn't already """
        if isinstance(s, bytes):
            return s
        else:
            return bytes(s, "ascii")

    # Convert input into bytestring
    input = b"\n".join(map(to_bytes, input)) + b"\n" \
            if isinstance(input, list) else to_bytes(input)

    # Convert expected into bytes if it isn't already
    if expected is not None:
        expected = to_bytes(expected)

    def decorator(fn):
        fn.io_set = (input, expected)

        @functools.wraps(fn)
        def wrapper(self):
            # Create pipe for child's stdin.
            child_read, parent_write = os.pipe()

            # Create pipe for child stdout.
            parent_read, child_write = os.pipe()

            # Create pipe for exceptions thrown by child.
            parent_read_error, child_write_error = os.pipe()

            def close_all(*fds):
                """Helper function that closes a list of file descriptors"""
                for fd in fds:
                    os.close(fd)

            pid = os.fork()

            # Parent process.
            if pid:
                close_all(child_read, child_write, child_write_error)

                with os.fdopen(parent_read_error, "rb") as error, \
                        os.fdopen(parent_read, "rb") as child_stdout:

                    # We use an additional `with` here because
                    # parent_write must be closed or the child will
                    # block reading for more stdin.
                    with os.fdopen(parent_write, "wb") as child_stdin:
                        child_stdin.write(input)

                    # Handle exceptions thrown by child as failed test.
                    err = error.read()
                    if err:
                        self.fail(err.decode())

                    output = child_stdout.read()
                    # Check expected stdout if provided.
                    if expected is not None:
                        self.assertEqual(output, expected)

            # pid will be zero in child process.
            else:
                try:
                    close_all(parent_read, parent_write, parent_read_error)
                    os.dup2(child_read, sys.stdin.fileno())
                    if expected is not None:
                        os.dup2(child_write, sys.stdout.fileno())
                    fn(self)
                except:
                    # Report any exception as failed test.
                    os.write(child_write_error,
                             traceback.format_exc().encode())
                finally:
                    close_all(child_read, child_write, child_write_error)
                    os._exit(0)
        return wrapper
    return decorator


def inheritIO(cls):
    for base in cls.__bases__:
        for name in dir(base):
            base_fn, cls_fn = getattr(base, name), getattr(cls, name)
            if hasattr(base_fn, "io_set") and not hasattr(cls_fn, "io_set"):
                setattr(cls, name, setIO(*getattr(base_fn, "io_set"))(cls_fn))

    return cls
