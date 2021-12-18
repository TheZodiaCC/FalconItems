class CodeLock extends Inventory_Base
{
	private bool isLocked;
	private bool isPasswordSet;
	private string password;
	
	
	void CodeLock()
	{
		RegisterNetSyncVariableBool("isLocked");
		RegisterNetSyncVariableBool("isPasswordSet");
	}
	
	override void EEInit()
    {
        super.EEInit();
		
		SetAllowDamage(false);
    }
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
		ctx.Write(isLocked);
		ctx.Write(isPasswordSet);
		ctx.Write(password);
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
		
		
		if ( !ctx.Read(isLocked) )
		{
			unlockServer();
			return false;
		}
		
		if ( !ctx.Read(isPasswordSet) )
		{		
			unlockServer();
			return false;
		}
		
		if ( !ctx.Read(password) )
		{
			unlockServer();
			return false;
		}

		return true;
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();		
		
		if ( GetGame().IsServer() )
		{
			EntityAI parent = GetHierarchyParent();
			if ( parent && parent.IsInherited( BaseBuildingBase ) )
			{
				if (isLocked || isPasswordSet)
				{
					lockServer();
				}
			}
		}		
		
		SetSynchDirty();
	}
	
	/*override void OnItemLocationChanged( EntityAI old_owner, EntityAI new_owner ) 
	{
		super.OnItemLocationChanged( old_owner, new_owner );
	
		if (isLockAttached())
		{
			lockServer();
		}	
	}*/	
	
	bool isLockAttached()
	{
		Fence fence = Fence.Cast( GetHierarchyParent() );
		
		if ( fence )
		{
			return true;
		}
		
		return false;
	}
	
	void lockServer()
	{
		if (GetGame().IsServer())
		{
			if (isLockAttached() && isPasswordSet)
			{
				Fence fence = Fence.Cast(GetHierarchyParent());
				
				InventoryLocation inventory_location = new InventoryLocation;
				GetInventory().GetCurrentInventoryLocation(inventory_location);	
					
				fence.GetInventory().SetSlotLock(inventory_location.GetSlot(), true);
				
				setIsLocked(true);
				SetTakeable(false);
				
				//fence.CloseFence();
			}
		}
	}
	
	void unlockServer()
	{
		if (GetGame().IsServer())
		{
			if (isLockAttached() && isPasswordSet)
			{
				Fence fence = Fence.Cast(GetHierarchyParent());
				
				InventoryLocation inventory_location = new InventoryLocation;
				GetInventory().GetCurrentInventoryLocation( inventory_location );			
				fence.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );			
		
				setIsLocked(false);
				
				//SetTakeable(true);
				
				fence.OpenFence();
			}	
		}
	}
	
	void removeLock()
	{
		if (GetGame().IsServer())
		{
			if (isLockAttached())
			{
				Fence fence = Fence.Cast(GetHierarchyParent());
				
				setIsLocked(false);
				
				InventoryLocation inventory_location = new InventoryLocation;
				GetInventory().GetCurrentInventoryLocation( inventory_location );			
				fence.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );
				
				fence.GetInventory().DropEntity(InventoryMode.SERVER, fence, this);
				SetPosition( fence.GetKitSpawnPosition() );
				
				PlaceOnSurface();
				
				SetTakeable(true);
				
				SetSynchDirty();
			}	
		}
		
	}
	
	void destroyLock()
	{
		if (GetGame().IsServer())
		{
			if (isLockAttached())
			{
				Fence fence = Fence.Cast(GetHierarchyParent());
				
				InventoryLocation inventory_location = new InventoryLocation;
				GetInventory().GetCurrentInventoryLocation( inventory_location );			
				fence.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );
				
				fence.GetInventory().DropEntity(InventoryMode.SERVER, fence, this);
				
				Delete();
			}	
		}
		
	}
	
	void setPassword(string value)
	{
		if (!isPasswordSet)
		{
			password = value;
		}
	}
	
	string getPassword()
	{
		return password;
	}
	
	void setPasswordSet(bool value)
	{
		isPasswordSet = value;
		SetTakeable(value);
	}
	
	bool getPasswordSet()
	{
		return isPasswordSet;
	}
	
	void setIsLocked(bool value)
	{
		isLocked = value;
		SetSynchDirty();
	}
	
	bool getIsLocked()
	{
		return isLocked;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionAttachToConstruction);
		AddAction(ActionOpenCodeLock);	
		AddAction(ActionCloseCodeLock);
	}
}