/**
 * NetXMS - open source network management system
 * Copyright (C) 2003-2017 Raden Solutions
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
package org.netxms.ui.eclipse.objectmanager.dialogs;

import org.eclipse.jface.dialogs.Dialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Shell;
import org.netxms.client.constants.RackAttributeType;
import org.netxms.client.constants.RackOrientation;
import org.netxms.client.objects.configs.RackPassiveElementConfigEntry;
import org.netxms.ui.eclipse.objectmanager.Messages;
import org.netxms.ui.eclipse.tools.WidgetHelper;
import org.netxms.ui.eclipse.widgets.LabeledSpinner;
import org.netxms.ui.eclipse.widgets.LabeledText;

/**
 * Rack attribute edit dialog
 */
public class RackPassiveElementEditDialog extends Dialog
{
   private final static String[] ORIENTATION = { "Fill", "Front", "Rear" };
   private final static String[] TYPE = { "Patch panel", "Filler panel", "Organiser panel" };
   
   private RackPassiveElementConfigEntry rackPassiveElement;
   private LabeledText rackPassiveElementName;
   private Combo rackPassiveElementType;
   private Combo rackOrientation;
   private LabeledSpinner rackPosition;
   
   /**
    * @param parentShell
    */
   public RackPassiveElementEditDialog(Shell parentShell, RackPassiveElementConfigEntry attribute)
   {
      super(parentShell);
      this.rackPassiveElement = attribute;
   }

   /* (non-Javadoc)
    * @see org.eclipse.jface.dialogs.Dialog#createDialogArea(org.eclipse.swt.widgets.Composite)
    */
   @Override
   protected Control createDialogArea(Composite parent)
   {
      if (rackPassiveElement == null)
         rackPassiveElement = new RackPassiveElementConfigEntry();
      
      Composite dialogArea = new Composite(parent, SWT.NONE);
      
      GridLayout layout = new GridLayout();
      layout.marginHeight = WidgetHelper.DIALOG_HEIGHT_MARGIN;
      layout.numColumns = 3;
      dialogArea.setLayout(layout);
      
      GridData gd = new GridData();
      gd.grabExcessHorizontalSpace = true;
      gd.horizontalAlignment = SWT.FILL;
      gd.horizontalSpan = 3;
      rackPassiveElementName = new LabeledText(dialogArea, SWT.NONE);
      rackPassiveElementName.setLabel("Name");
      rackPassiveElementName.setText(rackPassiveElement.getName());
      rackPassiveElementName.setLayoutData(gd);
      
      gd = new GridData();
      gd.grabExcessHorizontalSpace = true;
      gd.horizontalAlignment = SWT.FILL;
      rackPassiveElementType = WidgetHelper.createLabeledCombo(dialogArea, SWT.READ_ONLY, "Type", gd);
      rackPassiveElementType.setItems(TYPE);
      rackPassiveElementType.setText(TYPE[rackPassiveElement.getType().getValue()]);
      
      rackPosition = new LabeledSpinner(dialogArea, SWT.NONE);
      rackPosition.setLabel(Messages.get().RackPlacement_Position);
      rackPosition.setRange(1, 50);
      rackPosition.setSelection(rackPassiveElement.getPosition());
      
      gd = new GridData();
      gd.grabExcessHorizontalSpace = true;
      gd.horizontalAlignment = SWT.FILL;
      rackPosition.setLayoutData(gd);
      
      gd = new GridData();
      gd.grabExcessHorizontalSpace = true;
      gd.horizontalAlignment = SWT.FILL;
      rackOrientation = WidgetHelper.createLabeledCombo(dialogArea, SWT.READ_ONLY, "Orientation", gd);
      rackOrientation.setItems(ORIENTATION);
      rackOrientation.setText(ORIENTATION[rackPassiveElement.getOrientation().getValue()]);
      
      return dialogArea;
   }

   /* (non-Javadoc)
    * @see org.eclipse.jface.window.Window#configureShell(org.eclipse.swt.widgets.Shell)
    */
   @Override
   protected void configureShell(Shell newShell)
   {
      super.configureShell(newShell);
      newShell.setText((rackPassiveElement == null) ? "Create new attribute" : "Edit attribute");
   }

   /* (non-Javadoc)
    * @see org.eclipse.jface.dialogs.Dialog#okPressed()
    */
   @Override
   protected void okPressed()
   {      
      rackPassiveElement.setPosition(rackPosition.getSelection());
      rackPassiveElement.setOrientation(RackOrientation.getByValue(rackOrientation.getSelectionIndex()));
      rackPassiveElement.setName(rackPassiveElementType.getText());
      rackPassiveElement.setType(RackAttributeType.getByValue(rackPassiveElementType.getSelectionIndex()));
      super.okPressed();
   }
   
   /**
    * Get attribute config entry
    * 
    * @return attribute
    */
   public RackPassiveElementConfigEntry getPassiveElement()
   {
      return rackPassiveElement;
   }
}
