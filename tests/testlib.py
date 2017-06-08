#!/usr/bin/env python
import os
import ctypes
import unittest

from setio import setIO, inheritIO


class TestLib(unittest.TestCase):
    lib = ctypes.CDLL(os.environ.get("LIBCS50") or "build/usr/lib/libcs50.so")
    fn = None
    MAX = None
    assert_fn = unittest.TestCase.assertEqual

    @classmethod
    def openlib(cls, path):
        cls.lib = ctypes.CDLL(path)


class TestGetString(TestLib):
    fn = TestLib.lib.get_string
    fn.restype = ctypes.c_char_p

    @setIO(input="\n\r\n")
    def test_empty_lf_vs_crlf(self):
        lf, crlf = (self.fn(None) for _ in range(2))
        self.assert_fn(lf, b"")
        self.assert_fn(crlf, lf)

    @setIO(input=["This is a string", "This is a string\r"])
    def test_lf_vs_crlf(self):
        lf, crlf = (self.fn(None) for _ in range(2))
        self.assert_fn(lf, b"This is a string")
        self.assert_fn(lf, crlf)

    @setIO(input="")
    def test_eof(self):
        self.assert_fn(self.fn(None), None)

    @setIO(input="test string\n", expected="Prompt: ")
    def test_prompt(self):
        self.assert_fn(self.fn(b"Prompt: "), b"test string")


class TestGetChar(TestLib):
    fn = TestLib.lib.get_char

    # Assume signed char
    fn.restype = ctypes.c_byte
    MAX = 127

    # TODO: Figure out some way to determine char-signedness on platform
    # if char is signed:
    #     fn.restype = ctypes.c_byte
    #     MAX = 127 (ideally we'd check CHAR_BIT too?)
    # else:
    #     fn.restype = ctypes.c_char
    #     MAX = 255

    @setIO(input="", expected="")
    def test_return_max_on_error(self):
        self.assert_fn(self.fn(None), self.MAX)

    @setIO(input=["ab", "c"], expected="Retry: ")
    def test_multible_characters(self):
        self.assert_fn(self.fn(None), ord("c"))

    @setIO(input="A\n", expected="Custom prompt: ")
    def test_custom_prompt(self):
        self.assert_fn(self.fn(b"Custom prompt: "), ord("A"))


class TestGetLongLong(TestLib):
    fn = TestLib.lib.get_long_long
    fn.restype = ctypes.c_longlong
    MAX = 2 ** (ctypes.sizeof(ctypes.c_longlong) * 8 - 1) - 1

    @setIO(input="4\n", expected="")
    def test_basic_read_input(self):
        self.assert_fn(self.fn(None), 4)

    @setIO(input=["this is not a number", "3"], expected="Retry: ")
    def test_invalid_input(self):
        self.assert_fn(self.fn(None), 3)

    @setIO(input=["not a number", "50"],
           expected="Custom prompt: Custom prompt: ")
    def test_custom_prompt(self):
        self.assert_fn(self.fn(b"Custom prompt: "), 50)

    @setIO(input=[str(2**64), "9"], expected="Retry: ")
    def test_overflow_positive(self):
        self.assert_fn(self.fn(None), 9)

    @setIO(input=[str(-2**64), "73"], expected="Retry: ")
    def test_overflow_negative(self):
        self.assert_fn(self.fn(None), 73)

    @setIO(input="")
    def test_return_max_on_error(self):
        self.assert_fn(self.fn(None), self.MAX)

    @setIO(input=["123a", "-2"], expected="Retry: ")
    def test_trailing_character(self):
        self.assert_fn(self.fn(None), -2)

    @setIO(input=["12a3", "-4"], expected="Retry: ")
    def test_middle_character(self):
        self.assert_fn(self.fn(None), -4)

    @setIO(input=["a123", "0"], expected="Retry: ")
    def test_leading_character(self):
        self.assert_fn(self.fn(None), 0)

    @setIO(input=["not a number", "still not", "1262"],
           expected="")
    def test_empty_prompt(self):
        self.assert_fn(self.fn(b""), 1262)

    @setIO(input="123 \n", expected="Retry: ")
    def test_trailing_whitespace(self):
        self.assert_fn(self.fn(None), self.MAX)

    @setIO(input=" 123\n", expected="Retry: ")
    def test_leading_whitespace(self):
        self.assert_fn(self.fn(None), self.MAX)


@inheritIO
class TestGetInt(TestGetLongLong):
    MAX = 2 ** (ctypes.sizeof(ctypes.c_int) * 8 - 1) - 1
    fn = TestLib.lib.get_int
    fn.restype = ctypes.c_int

    @setIO(input=[str(MAX+1), "12"], expected="Retry: ")
    def test_input_overflow_under_long_max(self):
        self.assert_fn(self.fn(None), 12)

    @setIO(input=[str(-MAX-2), "21324"], expected="Retry: ")
    def test_input_overflow_over_long_min(self):
        self.assert_fn(self.fn(None), 21324)


@inheritIO
class TestGetDouble(TestGetLongLong):
    epsilon = 2 ** -52
    MAX = (2 ** 1023) * (2 - epsilon)
    fn = TestLib.lib.get_double
    fn.restype = ctypes.c_double

    def assert_fn(self, x, y):
        self.assertAlmostEqual(x, y, delta=self.epsilon)

    @setIO(input="4.23\n", expected="")
    def test_basic_read_input(self):
        self.assert_fn(self.fn(None), 4.23)

    @setIO(input="inf\n", expected="Retry: ")
    def test_dont_accept_inf(self):
        self.assert_fn(self.fn(None), self.MAX)

    @setIO(input="nan\n", expected="Retry: ")
    def test_dont_accept_nan(self):
        self.assert_fn(self.fn(None), self.MAX)

    @setIO(input=["1{0}.0".format("".join(("0" for _ in range(310)))),
                  "0.125"],
           expected="Retry: ")
    def test_overflow_positive(self):
        self.assert_fn(self.fn(None), 0.125)

    @setIO(input=["-1{0}.0".format("".join(("0" for _ in range(310)))),
                  "900"],
           expected="Retry: ")
    def test_overflow_negative(self):
        self.assert_fn(self.fn(None), 900)

    @setIO(input=["0.{0}1".format("".join(("0" for _ in range(310)))),
                  "-2.3"],
           expected="Retry: ")
    def test_underflow(self):
        self.assert_fn(self.fn(None), -2.3)


@inheritIO
class TestGetFloat(TestGetDouble):
    fn = TestLib.lib.get_float
    fn.restype = ctypes.c_float
    epsilon = 2 ** -23
    MAX = (2 - epsilon) * 2 ** 127


if __name__ == "__main__":
    unittest.main()
