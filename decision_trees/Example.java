package decision_trees;

import java.util.HashMap;

public class Example {
	private HashMap<Attribute, String> values;
	private Goal goal;

	public Example(HashMap<Attribute, String> values, Goal goal) {
		this.values = values;
		this.goal = goal;
	}

	public Goal getGoal() {
		return goal;
	}

	public String getValue(Attribute attr) {
		return values.get(attr);
	}

}
