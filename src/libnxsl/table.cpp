/* 
** NetXMS - Network Management System
** NetXMS Scripting Language Interpreter
** Copyright (C) 2003-2013 Victor Kirhenshtein
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** File: table.cpp
**
**/

#include "libnxsl.h"

/**
 * addRow() method
 */
NXSL_METHOD_DEFINITION(addRow)
{
   ((Table *)object->getData())->addRow();
   *result = new NXSL_Value;
   return 0;
}

/**
 * addColumn(name) method
 */
NXSL_METHOD_DEFINITION(addColumn)
{
   if (!argv[0]->isString())
      return NXSL_ERR_NOT_STRING;

   ((Table *)object->getData())->addColumn(argv[0]->getValueAsCString());
   *result = new NXSL_Value;
   return 0;
}

/**
 * get(row, column) method
 */
NXSL_METHOD_DEFINITION(get)
{
   if (!argv[0]->isInteger() || !argv[1]->isInteger())
      return NXSL_ERR_NOT_INTEGER;

   const TCHAR *value = ((Table *)object->getData())->getAsString(argv[0]->getValueAsInt32(), argv[1]->getValueAsInt32());
   *result = (value != NULL) ? new NXSL_Value(value) : new NXSL_Value;
   return 0;
}

/**
 * getColumnIndex(name) method
 */
NXSL_METHOD_DEFINITION(getColumnIndex)
{
   if (!argv[0]->isString())
      return NXSL_ERR_NOT_STRING;

   *result = new NXSL_Value((LONG)((Table *)object->getData())->getColumnIndex(argv[0]->getValueAsCString()));
   return 0;
}

/**
 * getColumnName(column) method
 */
NXSL_METHOD_DEFINITION(getColumnName)
{
   if (!argv[0]->isInteger())
      return NXSL_ERR_NOT_INTEGER;

   const TCHAR *value = ((Table *)object->getData())->getColumnName(argv[0]->getValueAsInt32());
   *result = (value != NULL) ? new NXSL_Value(value) : new NXSL_Value;
   return 0;
}

/**
 * set(row, column, value) method
 */
NXSL_METHOD_DEFINITION(set)
{
   if (!argv[0]->isInteger() || !argv[1]->isInteger())
      return NXSL_ERR_NOT_INTEGER;
   if (!argv[2]->isString())
      return NXSL_ERR_NOT_STRING;

   ((Table *)object->getData())->setAt(argv[0]->getValueAsInt32(), argv[1]->getValueAsInt32(), argv[2]->getValueAsCString());
   *result = new NXSL_Value;
   return 0;
}

/**
 * Implementation of "Table" class: constructor
 */
NXSL_TableClass::NXSL_TableClass() : NXSL_Class()
{
   _tcscpy(m_szName, _T("Table"));

   NXSL_REGISTER_METHOD(addColumn, 1);
   NXSL_REGISTER_METHOD(addRow, 0);
   NXSL_REGISTER_METHOD(get, 2);
   NXSL_REGISTER_METHOD(getColumnIndex, 1);
   NXSL_REGISTER_METHOD(getColumnName, 1);
   NXSL_REGISTER_METHOD(set, 3);
}

/**
 * Implementation of "Table" class: destructor
 */
NXSL_TableClass::~NXSL_TableClass()
{
}

/**
 * Object delete
 */
void NXSL_TableClass::onObjectDelete(NXSL_Object *object)
{
   delete (Table *)object->getData();
}

/**
 * Implementation of "Table" class: get attribute
 */
NXSL_Value *NXSL_TableClass::getAttr(NXSL_Object *object, const TCHAR *attr)
{
   NXSL_Value *value = NULL;
   Table *table = (Table *)object->getData();
   if (!_tcscmp(attr, _T("columnCount")))
   {
      value = new NXSL_Value((LONG)table->getNumColumns());
   }
   else if (!_tcscmp(attr, _T("rowCount")))
   {
      value = new NXSL_Value((LONG)table->getNumRows());
   }
   else if (!_tcscmp(attr, _T("title")))
   {
      value = new NXSL_Value(table->getTitle());
   }
   return value;
}
