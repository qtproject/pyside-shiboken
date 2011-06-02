#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# This file is part of the Shiboken Python Bindings Generator project.
#
# Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

import unittest
from minimal import Obj

class ExtObj(Obj):
    def __init__(self, objId):
        Obj.__init__(self, objId)
        self.virtual_method_called = False

    def virtualMethod(self, val):
        self.virtual_method_called = True
        return not Obj.virtualMethod(self, val)


class ObjTest(unittest.TestCase):

    def testNormalMethod(self):
        objId = 123
        obj = Obj(objId)
        self.assertEqual(obj.objId(), objId)

    def testVirtualMethod(self):
        obj = Obj(0)
        even_number = 8
        self.assertEqual(obj.virtualMethod(even_number), obj.callVirtualMethod(even_number))

    def testNormalMethodFromExtendedClass(self):
        objId = 123
        obj = ExtObj(objId)
        self.assertEqual(obj.objId(), objId)

    def testVirtualMethodFromExtendedClass(self):
        obj = ExtObj(0)
        even_number = 8
        self.assertEqual(obj.virtualMethod(even_number), obj.callVirtualMethod(even_number))
        self.assert_(obj.virtual_method_called)

if __name__ == '__main__':
    unittest.main()
