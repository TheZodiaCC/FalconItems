modded class MissionBase {
    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) {
            switch (id) {
				case 2138333: {
					menu = new MapMonitor;
					break;
				}
				case 2138215: {
					menu = new SafeCodeLock;
					break;
				}
				case 1321258: {
					menu = new CodeLockMenu;
					break;
				}
				case 2023215: {
					menu = new PlotPoleMonitor;
					break;
				}
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}