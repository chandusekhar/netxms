/**
 * NetXMS - open source network management system
 * Copyright (C) 2020 Raden Solutions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
package org.netxms.ui.eclipse.logviewer.actions;

import java.util.ArrayList;
import java.util.List;
import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.handlers.HandlerUtil;
import org.netxms.client.constants.ColumnFilterSetOperation;
import org.netxms.client.constants.ColumnFilterType;
import org.netxms.client.log.ColumnFilter;
import org.netxms.client.log.LogFilter;
import org.netxms.client.log.OrderingColumn;
import org.netxms.client.objects.AbstractNode;
import org.netxms.client.objects.AbstractObject;
import org.netxms.ui.eclipse.logviewer.views.LogViewer;
import org.netxms.ui.eclipse.tools.MessageDialogHelper;

/**
 * Handler for "show object windows event logs" command
 */
public class ShowObjectWindowsEventLog extends AbstractHandler
{
   /* (non-Javadoc)
    * @see org.eclipse.core.commands.AbstractHandler#execute(org.eclipse.core.commands.ExecutionEvent)
    */
   @Override
   public Object execute(ExecutionEvent event) throws ExecutionException
   {
      IWorkbenchWindow window = HandlerUtil.getActiveWorkbenchWindow(event);
      ISelection selection = window.getActivePage().getSelection();
      if ((selection == null) || !(selection instanceof IStructuredSelection) || selection.isEmpty())
         return null;
      
      ColumnFilter cf = new ColumnFilter();
      cf.setOperation(ColumnFilterSetOperation.OR);
      for(Object o : ((IStructuredSelection)selection).toList())
      {
         if (!(o instanceof AbstractObject))
            continue;
         cf.addSubFilter(new ColumnFilter((o instanceof AbstractNode) ? ColumnFilterType.EQUALS : ColumnFilterType.CHILDOF, ((AbstractObject)o).getObjectId()));
      }
      
      try
      {
         LogViewer view = (LogViewer)window.getActivePage().showView(LogViewer.ID, "WindowsEventLog", IWorkbenchPage.VIEW_ACTIVATE); //$NON-NLS-1$

         LogFilter filter = new LogFilter();
         filter.setColumnFilter("node_id", cf); //$NON-NLS-1$
         List<OrderingColumn> orderingColumns = new ArrayList<OrderingColumn>(1);
         orderingColumns.add(new OrderingColumn("event_timestamp", "Time", true)); //$NON-NLS-1$
         filter.setOrderingColumns(orderingColumns);
         
         view.queryWithFilter(filter);
      }
      catch(PartInitException e)
      {
         MessageDialogHelper.openError(window.getShell(), "Error", String.format("Cannot open log viewer: %s", e.getMessage()));
      }
      
      return null;
   }
}
