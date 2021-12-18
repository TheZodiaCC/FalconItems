class PlotPoleDataPackage
{
	ref array<string> ownersNames = new array<string>();
	int refresherTimeRemaining;
	int ownersCount;
	int maxObjectsCount;
	int objectsCount;
	int maxLevel;
	int currentLevel;
	
	void PlotPoleDataPackage(array<string> ownersNames, int refresherTimeRemaining, int ownersCount, int maxObjectsCount, int objectsCount, int maxLevel, int currentLevel)
	{
		this.ownersNames = ownersNames;
		this.refresherTimeRemaining = refresherTimeRemaining;
		this.ownersCount = ownersCount;
		this.maxObjectsCount = maxObjectsCount;
		this.objectsCount = objectsCount;
		this.maxLevel = maxLevel;
		this.currentLevel = currentLevel;
	}
}