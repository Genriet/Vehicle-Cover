modded class BoatScript
{
	protected bool m_CanAttachCamonet;
	protected string m_CamonetObjectName;
	protected string m_CamonetShapeableObjectName;
	protected string m_CamonetShapeableSlotName;
	protected bool m_CamonetShapeable = false;

	protected bool m_DropCamonet;
	protected float m_MaxSpeed;
	protected bool m_BlockGettingInWithCamonet;
	protected bool m_BlockAttachmentsWithCamonet;

	//Server-only
	protected float m_CamonetHealth;

	//Both
	protected bool m_HasCamonet;

	//Client-only
#ifndef SERVER
	protected EntityAI m_Camonet;
	protected bool m_LocalHasCamonet;
#endif

	void BoatScript()
	{
		RegisterNetSyncVariableBool("m_HasCamonet");
		VC_SetCamonetInfo();
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionVC_UncoverVehicle);
		AddAction(ActionVC_CoverVehicle);
	}

#ifdef SERVER
	override void EEInit()
	{
		super.EEInit();
		
		// May be redundant
		SetSynchDirty();
	}
#endif

	protected void VC_SetCamonetInfo()
	{
		if (GetDayZGame().GetVehicleCover_Config())
		{
			array<ref VC_Data> Vehicles = GetDayZGame().GetVehicleCover_Config().Vehicles;
			for (int i = 0; i < Vehicles.Count(); i++)
			{
				if (IsInherited(Vehicles[i].VehicleClassname.ToType()))
				{
					VC_Data data = Vehicles[i];
					break;
				}
			}

			if (data)
			{
				m_CamonetObjectName = data.CamonetClassname;
				m_CamonetShapeableObjectName = data.CamonetShapeableClassname;
				m_CamonetShapeableSlotName = data.CamonetShapeableSlot;
				m_DropCamonet = data.DropCamonet;
				m_MaxSpeed = data.SpeedToDrop;
				m_BlockGettingInWithCamonet = data.BlockGettingInWithCamonet;
				m_BlockAttachmentsWithCamonet = data.BlockAttachmentsWithCamonet;

				m_CanAttachCamonet = true;
			}
			else
			{
				m_CanAttachCamonet = false;
			}

			if (m_CanAttachCamonet)
			{
				// Checking for errors in json
				if (!GetGame().ConfigIsExisting("CfgVehicles " + m_CamonetObjectName))
				{
					ErrorEx("VehicleCover: " + GetType() + " CamonetObject: " + m_CamonetObjectName + " is misspelled or doesn't exist");
				}

				if ((m_CamonetShapeableObjectName == "" && m_CamonetShapeableSlotName != "") || (m_CamonetShapeableObjectName != "" && m_CamonetShapeableSlotName == ""))
				{
					if (m_CamonetShapeableObjectName == "")
					{
						ErrorEx("VehicleCover: " + GetType() + " camonetShapeableClass is not assigned, while camonetShapeableSlot is assigned.");
					}
					else
					{
						ErrorEx("VehicleCover: " + GetType() + " camonetShapeableSlot is not assigned, while camonetShapeableClass is assigned.");
					}
					m_CamonetShapeable = false;
				}
				else if (m_CamonetShapeableSlotName != "" && InventorySlots.GetSlotIdFromString(m_CamonetShapeableSlotName) == InventorySlots.INVALID)
				{
					ErrorEx("VehicleCover: " + GetType() + " CamonetShapeableSlotName: " + m_CamonetShapeableSlotName + " is not in attachments or is misspelled.");
					m_CamonetShapeable = false;
				}
				else if (m_CamonetShapeableObjectName != "" && !GetGame().ConfigIsExisting("CfgVehicles " + m_CamonetShapeableObjectName))
				{
					ErrorEx("VehicleCover: " + GetType() + " CamonetShapeableObject: " + m_CamonetShapeableObjectName + "is misspelled or doesn't exist");
					m_CamonetShapeable = false;
				}
				else
				{
					m_CamonetShapeable = true;
				}

				// No GetCarDoorsState() in BoatScript
				//foreach(string slot : m_DoorSlotsToCheck)
				//{
				//	if (InventorySlots.GetSlotIdFromString(slot) == InventorySlots.INVALID)
				//		ErrorEx("VehicleCover: " + GetType() + " Slot: " + slot + " in DoorSlotsToCheck is not in attachments or is misspelled.");
				//}
			}
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		ctx.Write(m_HasCamonet);
		ctx.Write(m_CamonetHealth);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_HasCamonet))
			return false;

		if (!ctx.Read(m_CamonetHealth))
			return false;

		return true;
	}

	bool VC_CanAttachCamonet()
	{
		return (m_CanAttachCamonet && !VC_HasCamonet());
	}
	
	bool VC_CamonetBlocksGettingIn()
	{
		return m_BlockGettingInWithCamonet;
	}

	bool VC_HasCamonet()
	{
		return m_HasCamonet;
	}

	protected bool VC_IsShapeableInSlot()
	{
		if (m_CamonetShapeable)
		{
			EntityAI Shapeable_item = FindAttachmentBySlotName(m_CamonetShapeableSlotName);

			if (Shapeable_item)
			{
				return true;
			}
		}
		return false;
	}

	void VC_TakeCamonetAndSpawn(PlayerBase player)
	{
		// Take camonet from player, save hp then delete it
		ItemBase Camonet_item = player.GetItemInHands();
		m_CamonetHealth = Camonet_item.GetHealth();
		Camonet_item.DeleteSafe();

		m_HasCamonet = true;
		SetSynchDirty();
	}

	void VC_ReturnCamonetAndDespawn(PlayerBase player)
	{
		// Give camonet back to player and set hp
		EntityAI Camonet_item = player.GetHumanInventory().CreateInHands("CamoNet");
		Camonet_item.SetHealth(m_CamonetHealth);

		m_HasCamonet = false;
		SetSynchDirty();
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		if (m_BlockAttachmentsWithCamonet && m_HasCamonet)
		{
			return false;
		}

		return super.CanReceiveAttachment(attachment, slotId);
	}

	override bool CanReleaseAttachment(EntityAI attachment)
	{
		if (m_BlockAttachmentsWithCamonet && m_HasCamonet)
		{
			return false;
		}

		return super.CanReleaseAttachment(attachment);
	}

	// Camonets themselves are client-only
#ifndef SERVER 
	// Potentially should fix desync after restart
	override void EEInit()
	{
		super.EEInit();

		if (m_LocalHasCamonet != m_HasCamonet)
		{
			m_LocalHasCamonet = m_HasCamonet;
			
			if (m_LocalHasCamonet)
			{
				VC_SpawnCamonet();
			}
			else
			{
				VC_DeleteCamonet();
			}
		}
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (m_LocalHasCamonet != m_HasCamonet)
		{
			m_LocalHasCamonet = m_HasCamonet;

			if (m_LocalHasCamonet)
			{
				VC_SpawnCamonet();
			}
			else
			{
				VC_DeleteCamonet();
			}
		}
	}

	protected void VC_SpawnCamonet()
	{
		VC_DeleteCamonet();

		if (!m_CamonetShapeable)
		{
			m_Camonet = EntityAI.Cast(GetGame().CreateObject(m_CamonetObjectName, vector.Zero, true));
			m_Camonet.SetOrientation("180 0 0");
			AddChild(m_Camonet, -1);
		}
		else if (VC_IsShapeableInSlot())
		{
			m_Camonet = EntityAI.Cast(GetGame().CreateObject(m_CamonetShapeableObjectName, vector.Zero, true));
			m_Camonet.SetOrientation("180 0 0");
			AddChild(m_Camonet, -1);
		}
		else
		{
			m_Camonet = EntityAI.Cast(GetGame().CreateObject(m_CamonetObjectName, vector.Zero, true));
			m_Camonet.SetOrientation("180 0 0");
			AddChild(m_Camonet, -1);
		}
	}

	protected void VC_DeleteCamonet()
	{
		if (m_Camonet)
		{
			RemoveChild(m_Camonet);
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(GetGame().ObjectDelete, m_Camonet);
			m_Camonet = null;
		}
	}

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		if (VC_HasCamonet() && m_CamonetShapeable && slot_name == m_CamonetShapeableSlotName)
		{
			VC_SpawnCamonet();
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		if (VC_HasCamonet() && m_CamonetShapeable && slot_name == m_CamonetShapeableSlotName)
		{
			VC_SpawnCamonet();
		}
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);

		if (VC_HasCamonet())
		{
			VC_DeleteCamonet();
		}
	}
#endif
};
