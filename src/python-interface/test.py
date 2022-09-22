import imp
import unittest
import partition_comparison as pc
import unittest


class TestRandError(unittest.TestCase):

    def test_1(self):

        a = [0, 1, 1, 1]
        b = [0, 1, 2, 2]

        rand_error = pc.RandError(a, b)
        self.assertAlmostEqual(rand_error.index(), 1/3)
        self.assertAlmostEqual(rand_error.error(), 2/3)

        rand_error = pc.RandError(a, b, False)
        self.assertAlmostEqual(rand_error.index(), 2/3)
        self.assertAlmostEqual(rand_error.error(), 1/3)

    def test_2(self):

        a = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
        b = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

        rand_error = pc.RandError(a, b, False)
        self.assertAlmostEqual(rand_error.index(), 0)
        self.assertAlmostEqual(rand_error.error(), 1)

        self.assertRaises(RuntimeError, pc.RandError, a, b)



if __name__ == "__main__":
    unittest.main()