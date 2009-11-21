#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# This file is part of the Shiboken Python Bindings Generator project.
#
# Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
#
# Contact: PySide team <contact@pyside.org>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# version 2.1 as published by the Free Software Foundation. Please
# review the following information to ensure the GNU Lesser General
# Public License version 2.1 requirements will be met:
# http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
# #
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
# 02110-1301 USA

'''Test cases for overload sorting'''

import sys
import unittest

from sample import SortedOverload, ImplicitBase, ImplicitTarget

class SimpleOverloadSorting(unittest.TestCase):

    def setUp(self):
        self.obj = SortedOverload()

    def testIntDouble(self):
        '''Overloads with int and double'''
        self.assertEqual(self.obj.overload(3), "int")
        self.assertEqual(self.obj.overload(3.14), "double")

    def testImplicitConvert(self):
        '''Overloads with implicit convertible types'''
        self.assertEqual(self.obj.overload(ImplicitTarget()), "ImplicitTarget")
        self.assertEqual(self.obj.overload(ImplicitBase()), "ImplicitBase")

    def testContainer(self):
        '''Overloads with containers arguments'''
        self.assertEqual(self.obj.overload([ImplicitBase()]), "list(ImplicitBase)")


    def testImplicitOnly(self):
        '''Passing an implicit convertible object to an overload'''
        self.assert_(self.obj.implicit_overload(ImplicitTarget()))

if __name__ == '__main__':
    unittest.main()