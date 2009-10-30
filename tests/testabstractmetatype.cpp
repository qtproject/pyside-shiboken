/*
* This file is part of the API Extractor project.
*
* Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
*
* Contact: PySide team <contact@pyside.org>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
* 02110-1301 USA
*
*/

#include "testabstractmetatype.h"
#include <QtTest/QTest>
#include "testutil.h"

void TestAbstractMetaType::testConstCharPtrType()
{
    const char* cppCode ="const char* justAtest();";
    const char* xmlCode = "<typesystem package=\"Foo\">\
        <primitive-type name='char'/>\
    </typesystem>";
    TestUtil t(cppCode, xmlCode);
    QCOMPARE(t.builder()->globalFunctions().size(), 1);
    AbstractMetaFunction* func = t.builder()->globalFunctions().first();
    AbstractMetaType* rtype = func->type();
    // Test properties of const char*
    QVERIFY(rtype);
    QCOMPARE(rtype->package(), QString());
    QCOMPARE(rtype->name(), QString("char"));
    QVERIFY(rtype->isConstant());
    QVERIFY(!rtype->isArray());
    QVERIFY(!rtype->isContainer());
    QVERIFY(!rtype->isObject());
    QVERIFY(rtype->isPrimitive());
    QVERIFY(rtype->isNativePointer());
    QVERIFY(!rtype->isQObject());
    QVERIFY(!rtype->isReference());
    QVERIFY(rtype->isTargetLangChar());
    QVERIFY(!rtype->isValue());
    QVERIFY(!rtype->isValuePointer());
}

void TestAbstractMetaType::testCharType()
{
    const char* cppCode ="char justAtest(); class A {};";
    const char* xmlCode = "<typesystem package=\"Foo\">\
    <primitive-type name='char'/>\
    <value-type name='A' />\
    </typesystem>";
    TestUtil t(cppCode, xmlCode);

    AbstractMetaClassList classes = t.builder()->classes();
    QCOMPARE(classes.size(), 1);
    QCOMPARE(classes.first()->package(), QString("Foo"));

    AbstractMetaFunctionList functions = t.builder()->globalFunctions();
    QCOMPARE(functions.size(), 1);
    AbstractMetaFunction* func = functions.first();
    AbstractMetaType* rtype = func->type();
    // Test properties of const char*
    QVERIFY(rtype);
    QCOMPARE(rtype->package(), QString());
    QCOMPARE(rtype->name(), QString("char"));
    QVERIFY(!rtype->isConstant());
    QVERIFY(!rtype->isArray());
    QVERIFY(!rtype->isContainer());
    QVERIFY(!rtype->isObject());
    QVERIFY(rtype->isPrimitive());
    QVERIFY(!rtype->isNativePointer());
    QVERIFY(!rtype->isQObject());
    QVERIFY(!rtype->isReference());
    QVERIFY(rtype->isTargetLangChar());
    QVERIFY(rtype->isValue());
    QVERIFY(!rtype->isValuePointer());
}

void TestAbstractMetaType::testTypedef()
{
    const char* cppCode ="\
    struct A {\
        void someMethod();\
    };\
    typedef A B;\
    typedef B C;";
    const char* xmlCode = "<typesystem package=\"Foo\">\
    <value-type name='C' />\
    </typesystem>";
    TestUtil t(cppCode, xmlCode);

    AbstractMetaClassList classes = t.builder()->classes();
    QCOMPARE(classes.size(), 1);
    AbstractMetaClass* c = classes.findClass("C");
    QVERIFY(c);
    QVERIFY(c->isTypeAlias());
}

void TestAbstractMetaType::testTypedefWithTemplates()
{
    const char* cppCode ="\
    template<typename T>\
    class A {};\
    \
    class B {};\
    typedef A<B> C;\
    \
    void func(C c);\
    ";
    const char* xmlCode = "<typesystem package=\"Foo\">\
    <container-type name='A' type='list'/>\
    <value-type name='B' />\
    </typesystem>";
    TestUtil t(cppCode, xmlCode);

    AbstractMetaClassList classes = t.builder()->classes();
    QCOMPARE(classes.size(), 1);
    AbstractMetaFunctionList functions = t.builder()->globalFunctions();
    QCOMPARE(functions.count(), 1);
    AbstractMetaFunction* function = functions.first();
    AbstractMetaArgumentList args = function->arguments();
    QCOMPARE(args.count(), 1);
    AbstractMetaArgument* arg = args.first();
    AbstractMetaType* metaType = arg->type();
    QCOMPARE(metaType->cppSignature(), QString("A<B >"));
    qDebug() << metaType->typeEntry()->isContainer();
//     QVERIFY(c->isTypeAlias());
}

QTEST_APPLESS_MAIN(TestAbstractMetaType)

#include "testabstractmetatype.moc"