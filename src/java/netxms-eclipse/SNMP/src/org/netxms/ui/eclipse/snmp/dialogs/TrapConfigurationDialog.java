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
package org.netxms.ui.eclipse.snmp.dialogs;

import org.eclipse.jface.dialogs.Dialog;
import org.eclipse.jface.viewers.TableViewer;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.layout.RowData;
import org.eclipse.swt.layout.RowLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;
import org.netxms.client.snmp.SnmpTrap;
import org.netxms.ui.eclipse.eventmanager.widgets.EventSelector;
import org.netxms.ui.eclipse.shared.IUIConstants;
import org.netxms.ui.eclipse.tools.WidgetHelper;

/**
 * Trap configuration dialog
 *
 */
public class TrapConfigurationDialog extends Dialog
{
	private SnmpTrap trap;
	private Text description;
	private Text oid;
	private EventSelector event;
	private Text eventTag;
	private TableViewer paramList;
	private Button buttonAdd;
	private Button buttonEdit;
	private Button buttonDelete;
	private Button buttonUp;
	private Button buttonDown;

	/**
	 * Creates trap configuration dialog
	 * 
	 * @param parentShell parent shell
	 * @param trap SNMP trap object to edit
	 */
	public TrapConfigurationDialog(Shell parentShell, SnmpTrap trap)
	{
		super(parentShell);
		this.trap = trap;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.jface.window.Window#configureShell(org.eclipse.swt.widgets.Shell)
	 */
	@Override
	protected void configureShell(Shell newShell)
	{
		super.configureShell(newShell);
		newShell.setText("Edit SNMP Trap Mapping");
	}

	/* (non-Javadoc)
	 * @see org.eclipse.jface.dialogs.Dialog#createDialogArea(org.eclipse.swt.widgets.Composite)
	 */
	@Override
	protected Control createDialogArea(Composite parent)
	{
		Composite dialogArea = (Composite)super.createDialogArea(parent);
		
		GridLayout layout = new GridLayout();
      layout.marginWidth = IUIConstants.DIALOG_WIDTH_MARGIN;
      layout.marginHeight = IUIConstants.DIALOG_HEIGHT_MARGIN;
      layout.verticalSpacing = WidgetHelper.OUTER_SPACING;
		dialogArea.setLayout(layout);
		
		description = WidgetHelper.createLabeledText(dialogArea, SWT.BORDER, 300, "Description", trap.getDescription(), WidgetHelper.DEFAULT_LAYOUT_DATA);
		oid = WidgetHelper.createLabeledText(dialogArea, SWT.BORDER, 300, "Trap OID", trap.getObjectId().toString(), WidgetHelper.DEFAULT_LAYOUT_DATA);
		
		event = new EventSelector(dialogArea, SWT.NONE);
		event.setLabel("Event");
		event.setEventCode(trap.getEventCode());
		GridData gd = new GridData();
		gd.horizontalAlignment = SWT.FILL;
		gd.grabExcessHorizontalSpace = true;
		event.setLayoutData(gd);
		
		eventTag = WidgetHelper.createLabeledText(dialogArea, SWT.BORDER, SWT.DEFAULT, "User Tag", trap.getUserTag(), WidgetHelper.DEFAULT_LAYOUT_DATA);
		
		Label label = new Label(dialogArea, SWT.NONE);
		label.setText("Parameters");
		
		Composite paramArea = new Composite(dialogArea, SWT.NONE);
		gd = new GridData();
		gd.horizontalAlignment = SWT.FILL;
		gd.grabExcessHorizontalSpace = true;
		paramArea.setLayoutData(gd);
		layout = new GridLayout();
		layout.numColumns = 2;
		layout.marginHeight = 0;
		layout.marginWidth = 0;
		paramArea.setLayout(layout);

		paramList = new TableViewer(paramArea, SWT.BORDER | SWT.FULL_SELECTION);
		gd = new GridData();
		gd.horizontalAlignment = SWT.FILL;
		gd.grabExcessHorizontalSpace = true;
		gd.verticalAlignment = SWT.FILL;
		gd.grabExcessVerticalSpace = true;
		gd.widthHint = 300;
		paramList.getTable().setLayoutData(gd);
		
		Composite buttonArea = new Composite(paramArea, SWT.NONE);
		RowLayout btnLayout = new RowLayout();
		btnLayout.type = SWT.VERTICAL;
		btnLayout.marginBottom = 0;
		btnLayout.marginLeft = 0;
		btnLayout.marginRight = 0;
		btnLayout.marginTop = 0;
		btnLayout.fill = true;
		btnLayout.spacing = WidgetHelper.OUTER_SPACING;
		buttonArea.setLayout(btnLayout);
		
		buttonAdd = new Button(buttonArea, SWT.PUSH);
		buttonAdd.setText("&Add...");
		buttonAdd.setLayoutData(new RowData(WidgetHelper.BUTTON_WIDTH_HINT, SWT.DEFAULT));
		
		buttonEdit = new Button(buttonArea, SWT.PUSH);
		buttonEdit.setText("&Edit...");
		
		buttonDelete = new Button(buttonArea, SWT.PUSH);
		buttonDelete.setText("&Delete");
		
		buttonUp = new Button(buttonArea, SWT.PUSH);
		buttonUp.setText("Move &up");
		
		buttonDown = new Button(buttonArea, SWT.PUSH);
		buttonDown.setText("Move &down");
		
		return dialogArea;
	}
}
