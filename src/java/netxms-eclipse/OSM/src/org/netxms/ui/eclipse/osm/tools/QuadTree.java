/**
 * NetXMS - open source network management system
 * Copyright (C) 2003-2011 Victor Kirhenshtein
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
package org.netxms.ui.eclipse.osm.tools;

import java.util.ArrayList;
import java.util.List;

/**
 * Quad tree implementation
 */
public class QuadTree<Value>
{
	/**
	 * Internal helper class - tree node representation
	 */
	private class Node
	{
		double x, y;
		Node NW, NE, SW, SE;
		Value value;
		
		Node(double x, double y, Value value)
		{
			this.x = x;
			this.y = y;
			this.value = value;
		}
	}
	
	private Node root;
	
	/**
	 * Insert new entry
	 * 
	 * @param x
	 * @param y
	 * @param value
	 */
	public void insert(double x, double y, Value value)
	{
		root = insert(root, x, y, value);
	}
	
	/**
	 * Internal insert implementation
	 * 
	 * @param n
	 * @param x
	 * @param y
	 * @param value
	 * @return
	 */
	private Node insert(Node n, double x, double y, Value value)
	{
		if (n == null)
			return new Node(x, y, value);
		
		if ((x < n.x) && (y < n.y))
			n.SW = insert(n.SW, x, y, value);
		else if ((x < n.x) && (y >= n.y))
			n.NW = insert(n.NW, x, y, value);
		else if ((x >= n.x) && (y < n.y))
			n.SE = insert(n.SE, x, y, value);
		else if ((x >= n.x) && (y >= n.y))
			n.NE = insert(n.NE, x, y, value);
		
		return n;
	}
	
	/**
	 * Query tree for all values inside given area.
	 * 
	 * @param area rectangular area
	 * @return list of all values within given area
	 */
	public List<Value> query(Area area)
	{
		List<Value> result = new ArrayList<Value>();
		query(root, result, area);
		return result;
	}
	
	/**
	 * Internal query implementation
	 * 
	 * @param n current node
	 * @param result result set
	 * @param area area
	 */
	private void query(Node n, List<Value> result, Area area)
	{
		if (n == null)
			return;
		
		if (area.contains(n.x, n.y))
			result.add(n.value);
		
		if ((area.getxLow() < n.x) && (area.getyLow() < n.y))
			query(n.SW, result, area);
		if ((area.getxLow() < n.x) && (area.getyHigh() >= n.y))
			query(n.NW, result, area);
		if ((area.getxHigh() >= n.x) && (area.getyLow() < n.y))
			query(n.SE, result, area);
		if ((area.getxHigh() >= n.x) && (area.getyHigh() >= n.y))
			query(n.NE, result, area);
	}
}
