package decision_trees;

import java.util.HashSet;
import java.util.Iterator;

public class Attribute implements Iterable<String> {
	private String name;
	private HashSet<String> values;
	boolean numeric = false;
	private double splitPoint;

	public Attribute(String name, HashSet<String> values) {
		this.name = name;
		this.values = values;
	}

	public boolean validValue(String value) {
		if (values.contains("%numeric")) {
			try {
				Double.parseDouble(value);
			} catch (NumberFormatException e) {
				return false;
			}
			return true;
		} else {
			return values.contains(value);
		}
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Attribute other = (Attribute) obj;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return name;
	}

	@Override
	public Iterator<String> iterator() {
		return values.iterator();
	}

	public HashSet<String> getValues() {
		return values;
	}

	public boolean test(String attributeValue, Example example) {
		String ex = example.getValue(this);
		if (numeric) {
			double d = Double.parseDouble(ex);
			if (attributeValue.equals(">" + splitPoint) && d > splitPoint
					|| attributeValue.equals("<=" + splitPoint)
					&& d <= splitPoint) {
				return true;
			} else {
				return false;
			}
		} else {
			return attributeValue.equals(ex);
		}
	}

	public void setSplitPoint(double splitPoint) {
		this.splitPoint = splitPoint;
		values.clear();
		values.add(">" + splitPoint);
		values.add("<=" + splitPoint);
		numeric = true;
	}

	public String getKeyIfNumerical(String value) {
		if (numeric) {
			double d = Double.parseDouble(value);
			if (d > splitPoint) {
				return ">" + splitPoint;
			} else {
				return "<=" + splitPoint;
			}
		} else {
			return value;
		}
	}

}
