/**
 * NetXMS - open source network management system
 * Copyright (C) 2003-2010 Victor Kirhenshtein
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
package org.netxms.ui.eclipse.topology.views.helpers;

import java.util.HashMap;
import java.util.Map;
import org.eclipse.jface.viewers.ITableLabelProvider;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.swt.graphics.Image;
import org.netxms.client.ConnectionPoint;
import org.netxms.client.NXCSession;
import org.netxms.client.objects.GenericObject;
import org.netxms.ui.eclipse.shared.ConsoleSharedData;
import org.netxms.ui.eclipse.topology.views.HostSearchResults;

/**
 * Label provider for connection point objects
 *
 */
public class ConnectionPointLabelProvider extends LabelProvider implements ITableLabelProvider
{
	private Map<Long, String> cachedObjectNames = new HashMap<Long, String>();
	
	/* (non-Javadoc)
	 * @see org.eclipse.jface.viewers.ITableLabelProvider#getColumnImage(java.lang.Object, int)
	 */
	@Override
	public Image getColumnImage(Object element, int columnIndex)
	{
		return null;
	}
	
	/**
	 * Get (cached) object name by object ID
	 * @param id object id
	 * @return object name
	 */
	private String getObjectName(long id)
	{
		if (id == 0)
			return "";
		
		String name = cachedObjectNames.get(id);
		if (name == null)
		{
			GenericObject object = ((NXCSession)ConsoleSharedData.getSession()).findObjectById(id);
			name = (object != null) ? object.getObjectName() : "<unknown>";
			cachedObjectNames.put(id, name);
		}
		return name;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.jface.viewers.ITableLabelProvider#getColumnText(java.lang.Object, int)
	 */
	@Override
	public String getColumnText(Object element, int columnIndex)
	{
		ConnectionPoint cp = (ConnectionPoint)element;
		switch(columnIndex)
		{
			case HostSearchResults.COLUMN_SEQUENCE:
				return Integer.toString((Integer)cp.getData() + 1);
			case HostSearchResults.COLUMN_NODE:
				return getObjectName(cp.getLocalNodeId());
			case HostSearchResults.COLUMN_INTERFACE:
				return getObjectName(cp.getLocalInterfaceId());
			case HostSearchResults.COLUMN_MAC_ADDRESS:
				return cp.getLocalMacAddress().toString();
			case HostSearchResults.COLUMN_SWITCH:
				return getObjectName(cp.getNodeId());
			case HostSearchResults.COLUMN_PORT:
				return getObjectName(cp.getInterfaceId());
		}
		return null;
	}
}
