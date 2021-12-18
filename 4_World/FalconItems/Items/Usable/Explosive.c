class Explosive extends Inventory_Base
{
	ref Timer explosionTimer = new Timer;
	ref Timer beepTimer = new Timer;
	const float explosionTime = 7;
	private bool deployed;
	
	ref EffectSound	beepSoundEffect;
	
	void Explosive()
	{
		deployed = false;
		
		RegisterNetSyncVariableBool("deployed");
	}
	
	override void EEInit()
	{
		super.EEInit();
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionTogglePlaceObject);
		AddAction(ActionDeployObject);
	}

	override bool IsDeployable()
	{
		return true;
	}

	override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
	{
		if (GetGame().IsClient())
		{
			PlaySoundSetLoop(beepSoundEffect, "c4_beep_SoundSet", 0.1, 0.8);
			beepTimer.Run(explosionTime, this, "stopBeepSound");
		}
		
		if (GetGame().IsServer())
		{
			deployed = true;
			
			explosionTimer.Run(explosionTime, this, "triggerExplosive");
		}
	}
	
	override bool CanPutInCargo(EntityAI parent)
	{
		if (!deployed)
		{
			return super.CanPutInCargo(parent);
		}
		else
		{
			return false;
		}
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		if (!deployed)
		{
			return super.CanPutIntoHands(parent);
		}
		else
		{
			return false;
		}
	}
	
	void stopBeepSound()
	{
		StopSoundSet(beepSoundEffect);
	}
	
	void triggerExplosive()
	{
		//StopSoundSet(beepSoundEffect);
		
		Explode(DT_EXPLOSION, "Explosive_Ammo");
		Delete();
	}
}