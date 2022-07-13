class EL_GesturesControllerComponentClass : ScriptComponentClass
{
}

enum EL_ECharacterGestures
{
    SURRENDER = 2  // this number is the same as you checked on the state machine
}

class EL_GesturesControllerComponent : ScriptComponent
{
	protected CharacterControllerComponent m_CharacterController;
	protected BaseWeaponManagerComponent m_WeaponManager;
	protected InputManager m_InputManager;
	
	override void OnPostInit(IEntity owner)
	{
		m_CharacterController = CharacterControllerComponent.Cast(GetOwner().FindComponent(CharacterControllerComponent));
		m_WeaponManager = BaseWeaponManagerComponent.Cast(GetOwner().FindComponent(BaseWeaponManagerComponent));
		m_InputManager = GetGame().GetInputManager();
        m_InputManager.AddActionListener("EL_GestureSurrender", EActionTrigger.DOWN, OnSurrender);
        m_InputManager.AddActionListener("EL_GestureSurrender", EActionTrigger.UP, OnSurrender);
	}
	
	void OnSurrender( float value = 0.0, EActionTrigger reason = 0 )
	{
		if ( reason == EActionTrigger.DOWN )
		{
			
			if(m_WeaponManager.GetCurrent() && m_WeaponManager.GetCurrent().GetWeaponType() != EWeaponType.WT_NONE) m_CharacterController.TryEquipRightHandItem(null, EEquipItemType.EEquipTypeUnarmed);
			else 
			{
				m_InputManager.ActivateContext("CharacterRestrainedContext", 100000000);
				m_CharacterController.TryStartCharacterGesture(EL_ECharacterGestures.SURRENDER);
			}
		} 
		else if ( reason == EActionTrigger.UP )
		{
			m_CharacterController.StopCharacterGesture();
			m_InputManager.ActivateContext("CharacterRestrainedContext");      // Activates the context for 0 seconds
		}
	}	
}
