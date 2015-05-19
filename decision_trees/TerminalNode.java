package decision_trees;

public class TerminalNode implements DecisionNode {
	private Goal goal;

	public TerminalNode(Goal goal) {
		this.goal = goal;
	}

	@Override
	public String print(int level) {
		return ": " + goal.toString();
	}

	@Override
	public boolean isTerminal() {
		return true;
	}

}
