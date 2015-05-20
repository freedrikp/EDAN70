package decision_trees;

public class Pair implements Comparable<Pair> {

	private boolean classification;
	private double value;

	public Pair(double value, boolean classification) {
		this.value = value;
		this.classification = classification;
	}

	@Override
	public int compareTo(Pair p) {
		return Double.compare(value, p.value);
	}

	public String toString() {
		return "val: " + value + " class " + classification;
	}

	public double getValue() {
		return value;

	}

	public boolean getClassification() {
		return classification;
	}
}
