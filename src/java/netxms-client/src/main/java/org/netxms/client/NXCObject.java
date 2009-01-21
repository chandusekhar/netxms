/**
 * Generic NetXMS object class 
 */

package org.netxms.client;

import java.util.Map;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.net.InetAddress;
import org.netxms.base.*;

public class NXCObject
{
	// Object classes
	public static final int OBJECT_GENERIC        = 0;
	public static final int OBJECT_SUBNET         = 1;
	public static final int OBJECT_NODE           = 2;
	public static final int OBJECT_INTERFACE      = 3;
	public static final int OBJECT_NETWORK        = 4;
	public static final int OBJECT_CONTAINER      = 5;
	public static final int OBJECT_ZONE           = 6;
	public static final int OBJECT_SERVICEROOT    = 7;
	public static final int OBJECT_TEMPLATE       = 8;
	public static final int OBJECT_TEMPLATEGROUP  = 9;
	public static final int OBJECT_TEMPLATEROOT   = 10;
	public static final int OBJECT_NETWORKSERVICE = 11;
	public static final int OBJECT_VPNCONNECTOR   = 12;
	public static final int OBJECT_CONDITION      = 13;
	public static final int OBJECT_CLUSTER        = 14;
	
	// Status codes
	public static final int STATUS_NORMAL         = 0;
	public static final int STATUS_WARNING        = 1;
	public static final int STATUS_MINOR          = 2;
	public static final int STATUS_MAJOR          = 3;
	public static final int STATUS_CRITICAL       = 4;
	public static final int STATUS_UNKNOWN        = 5;
	public static final int STATUS_UNMANAGED      = 6;
	public static final int STATUS_DISABLED       = 7;
	public static final int STATUS_TESTING        = 8;
	
	// Associated client session
	private NXCSession session = null;
	
	// Generic object attributes
	private long objectId = 0;
	private String objectName;
	private int objectClass;	// NetXMS object class
	private int status = STATUS_UNKNOWN;
	private boolean isDeleted = false;
	private InetAddress primaryIP;
	private String comments;
	private HashSet<Long> parents = new HashSet<Long>(0);
	private HashSet<Long> childs = new HashSet<Long>(0);
	private Map<String, String> customAttributes = new HashMap<String, String>(0);
	
	private boolean inheritAccessRights = true;
	private HashSet<NXCAccessListElement> accessList = new HashSet<NXCAccessListElement>(0);


	/**
	 * Create object from NXCP message
	 * @param msg Message to create object from
	 * @param session Associated client session
	 */
	
	NXCObject(final NXCPMessage msg, final NXCSession session)
	{
		int i, count;
		long id, id2;
		
		this.session = session;
		
		objectId = msg.getVariableAsInteger(NXCPCodes.VID_OBJECT_ID);
		objectName = msg.getVariableAsString(NXCPCodes.VID_OBJECT_NAME);
		objectClass = msg.getVariableAsInteger(NXCPCodes.VID_OBJECT_CLASS);
		primaryIP = msg.getVariableAsInetAddress(NXCPCodes.VID_IP_ADDRESS);
		isDeleted = msg.getVariableAsBoolean(NXCPCodes.VID_IS_DELETED);
		
		// Parents
		count = msg.getVariableAsInteger(NXCPCodes.VID_PARENT_CNT);
		for(i = 0, id = NXCPCodes.VID_PARENT_ID_BASE; i < count; i++, id++)
		{
			parents.add(msg.getVariableAsInt64(id));
		}

		// Childs
		count = msg.getVariableAsInteger(NXCPCodes.VID_CHILD_CNT);
		for(i = 0, id = NXCPCodes.VID_CHILD_ID_BASE; i < count; i++, id++)
		{
			childs.add(msg.getVariableAsInt64(id));
		}
		
		// Custom attributes
		count = msg.getVariableAsInteger(NXCPCodes.VID_NUM_CUSTOM_ATTRIBUTES);
		for(i = 0, id = NXCPCodes.VID_CUSTOM_ATTRIBUTES_BASE; i < count; i++, id += 2)
		{
			customAttributes.put(msg.getVariableAsString(id), msg.getVariableAsString(id + 1));
		}
		
		// Access list
		inheritAccessRights = msg.getVariableAsBoolean(NXCPCodes.VID_INHERIT_RIGHTS);
		count = msg.getVariableAsInteger(NXCPCodes.VID_ACL_SIZE);
		for(i = 0, id = NXCPCodes.VID_ACL_USER_BASE, id2 = NXCPCodes.VID_ACL_RIGHTS_BASE; i < count; i++, id++, id2++)
		{
			accessList.add(new NXCAccessListElement(msg.getVariableAsInteger(id), msg.getVariableAsInteger(id2)));
		}
	}


	/**
	 * @return Iterator for list of parent objects
	 */
	public Iterator<Long> getParents()
	{
		return parents.iterator();
	}


	/**
	 * @return Iterator for list of child objects
	 */
	public Iterator<Long> getChilds()
	{
		return childs.iterator();
	}


	/**
	 * @return Iterator for access list
	 */
	public Iterator<NXCAccessListElement> getAccessList()
	{
		return accessList.iterator();
	}


	/**
	 * @return the comments
	 */
	public String getComments()
	{
		return comments;
	}


	/**
	 * @return the objectId
	 */
	public long getObjectId()
	{
		return objectId;
	}


	/**
	 * @return the objectName
	 */
	public String getObjectName()
	{
		return objectName;
	}


	/**
	 * @return the primaryIP
	 */
	public InetAddress getPrimaryIP()
	{
		return primaryIP;
	}


	/**
	 * @return the status
	 */
	public int getStatus()
	{
		return status;
	}


	/**
	 * @return the isDeleted
	 */
	public boolean isDeleted()
	{
		return isDeleted;
	}


	/**
	 * @return the inheritAccessRights
	 */
	public boolean isInheritAccessRights()
	{
		return inheritAccessRights;
	}


	/**
	 * Check if given object is direct or indirect parent
	 * 
	 * @param objectId ID of object to check
	 */
	public boolean isParent(final long objectId)
	{
		boolean rc = false;
		
		synchronized(parents)
		{
			final Iterator<Long> it = parents.iterator();
			for(int i = 0; it.hasNext(); i++)
			{
				long id = it.next();
				if (id == objectId)
				{
					// Direct parent
					rc = true;
					break;
				}
				NXCObject object = session.findObjectById(id);
				if (object != null)
				{
					if (object.isParent(objectId))
					{
						rc = true;
						break;
					}
				}
			}
		}		
		return rc;
	}
	
	
	/**
	 * @return List of parent objects
	 */
	public NXCObject[] getParentsAsArray()
	{
		final NXCObject[] list;
		synchronized(parents)
		{
			list = new NXCObject[parents.size()];
			final Iterator<Long> it = parents.iterator();
			for(int i = 0; it.hasNext(); i++)
			{
				list[i] = session.findObjectById(it.next());
			}
		}
		return list;
	}


	/**
	 * @return List of child objects
	 */
	public NXCObject[] getChildsAsArray()
	{
		final NXCObject[] list;
		synchronized(childs)
		{
			list = new NXCObject[childs.size()];
			final Iterator<Long> it = childs.iterator();
			for(int i = 0; it.hasNext(); i++)
			{
				list[i] = session.findObjectById(it.next());
			}
		}
		return list;
	}

	
	/**
	 * @return Number of parent objects
	 */
	public int getNumberOfParents()
	{
		return parents.size();
	}


	/**
	 * @return Number of child objects
	 */
	public int getNumberOfChilds()
	{
		return childs.size();
	}


	/**
	 * @return the objectClass
	 */
	public int getObjectClass()
	{
		return objectClass;
	}
}
