package decision_trees;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Set;

import umontreal.iro.lecuyer.probdist.ChiSquareDist;

public class DecisionTreeAlgorithm {
	private Relation rel;

	public DecisionTreeAlgorithm(Relation rel) {
		this.rel = rel;
	}

	public DecisionNode dtl() {
		return decisionTreeLearning(rel.getExamples(), rel.getAttributes(),
				rel.getExamples());
	}

	private boolean hasOnlyTerminalLeaves(Collection<DecisionNode> branches) {
		for (DecisionNode node : branches) {
			if (!node.isTerminal()) {
				return false;
			}
		}
		return true;

	}

	public DecisionNode pruning(DecisionNode tree) {
		if (tree.isTerminal()) {
			return tree;
		} else {
			AttributeNode hypothesis = (AttributeNode) tree;
			if (hasOnlyTerminalLeaves(hypothesis.getValueOfBranches())) {
				double deviation = deviation(hypothesis);
				int size = hypothesis.getBranches().size();
				if(size>1){
					size--;
				}
				double probability = ChiSquareDist.cdf(size, 4, deviation);
				if (probability >= 0.95) {
					return pluralityValue(hypothesis.getExamples());
				} else {
					return hypothesis;
				}

			} else {
				AttributeNode newTree = new AttributeNode(
						hypothesis.getAttribute(), hypothesis.getExamples());
				HashMap<String, DecisionNode> branches = hypothesis
						.getBranches();
				Set<String> keys = branches.keySet();
				for (String key : keys) {
					newTree.addBranch(key, pruning(branches.get(key)));
				}
				if (hasOnlyTerminalLeaves(newTree.getValueOfBranches())) {
					return pruning(newTree);
				} else {
					return newTree;
				}
			}
		}
	}

	private double deviation(AttributeNode node) {
		Attribute attr = node.getAttribute();
		ArrayList<Example> examples = node.getExamples();
		HashMap<String, Integer> positives = new HashMap<String, Integer>();
		HashMap<String, Integer> negatives = new HashMap<String, Integer>();
		int totPos = countExamples(attr, examples, positives, negatives);
		double calc = calcDeviation(attr, positives, negatives, totPos,
				examples.size());
		if(node.getAttribute().toString().equals("'insu'")){
		}
		return calc;
	}

	private double calcDeviation(Attribute attr,
			HashMap<String, Integer> positives,
			HashMap<String, Integer> negatives, int totPos, int examplesSize) {
		Set<String> keys = attr.getValues();
		double deviationSum = 0;
		for (String s : keys) {
			int positive = positives.get(s) == null ? 0 : positives.get(s);
			int negative = negatives.get(s) == null ? 0 : negatives.get(s);
			double estimateP = estimatedValue(positive, negative, totPos,
					examplesSize);
			double estimateN = estimatedValue(positive, negative, examplesSize
					- totPos, examplesSize);
			if(estimateP > 0 || estimateN >0){
				deviationSum += Math.pow(positive - estimateP, 2) / estimateP
						+ Math.pow(negative - estimateN, 2) / estimateN;
			}
		}
		return deviationSum;
	}

	private double estimatedValue(int p, int n, int totPart, int examplesSize) {
		return totPart * ((double) (p + n)) / examplesSize;
	}

	private DecisionNode decisionTreeLearning(ArrayList<Example> examples,
			ArrayList<Attribute> attributes, ArrayList<Example> parentExamples) {
		if (examples.isEmpty()) {
			return pluralityValue(parentExamples);
		} else if (hasSameGoals(examples)) {
			return new TerminalNode(examples.get(0).getGoal());
		} else if (attributes.isEmpty()) {
			return pluralityValue(examples);
		} else {
			Attribute attr = mostImporatant(attributes, examples);
			AttributeNode root = new AttributeNode(attr, examples);
			for (String value : attr) {
				ArrayList<Example> rootExamples = new ArrayList<Example>();
				for (Example ex : examples) {
					if (attr.test(value, ex)) {
						rootExamples.add(ex);
					}
				}
				ArrayList<Attribute> newAttributes = new ArrayList<Attribute>();
				for (Attribute a : attributes) {
					if (!a.equals(attr)) {
						newAttributes.add(a);
					}
				}
				root.addBranch(
						value,
						decisionTreeLearning(rootExamples, newAttributes,
								examples));
			}
			return root;
		}
	}

	private Attribute mostImporatant(ArrayList<Attribute> attributes,
			ArrayList<Example> examples) {
		double max = -1;
		Attribute attribute = null;
		for (Attribute attr : attributes) {
			double temp = calculateGain(attr, examples);
			if (temp > max) {
				attribute = attr;
				max = temp;
			}
		}
		return attribute;
	}

	private boolean hasSameGoals(ArrayList<Example> examples) {
		Goal g = examples.get(0).getGoal();
		for (Example ex : examples) {
			if (!g.equals(ex.getGoal())) {
				return false;
			}
		}
		return true;
	}

	private DecisionNode pluralityValue(ArrayList<Example> examples) {
		HashMap<Goal, Integer> map = new HashMap<Goal, Integer>();
		for (Example ex : examples) {
			int i = 1;
			if (map.containsKey(ex.getGoal())) {
				i = map.get(ex.getGoal());
				i++;
			}
			map.put(ex.getGoal(), i);
		}
		int occs = 0;
		Goal g = null;
		for (Entry<Goal, Integer> entry : map.entrySet()) {
			if (entry.getValue() > occs) {
				occs = entry.getValue();
				g = entry.getKey();
			}
		}
		return new TerminalNode(g);
	}

	private double calculateGain(Attribute attr, ArrayList<Example> examples) {
		HashMap<String, Integer> positives = new HashMap<String, Integer>();
		HashMap<String, Integer> negatives = new HashMap<String, Integer>();
		int totPos = countExamples(attr, examples, positives, negatives);
		double temp = bFunc(totPos, examples.size() - totPos);
		temp -= remainder(attr, positives, negatives, examples);
		return temp;

	}

	private double remainder(Attribute attr,
			HashMap<String, Integer> positives,
			HashMap<String, Integer> negatives, ArrayList<Example> examples) {
		Set<String> keys = attr.getValues();
		double sum = 0;
		for (String s : keys) {
			int positive = positives.get(s) == null ? 0 : positives.get(s);
			int negative = negatives.get(s) == null ? 0 : negatives.get(s);
			sum += (((double) (positive + negative)) / examples.size())
					* bFunc(positive, negative);
		}
		return sum;
	}

	private double bFunc(int p, int n) {
		double q = ((double) (p)) / (p + n);
		if (q > 0 && q < 1) {
			return -(q * (Math.log(q) / Math.log(2)) + (1 - q)
					* (Math.log(1 - q) / Math.log(2)));
		} else {
			return Math.log(1) / Math.log(2);
		}

	}

	public int countExamples(Attribute attr, ArrayList<Example> examples,
			HashMap<String, Integer> positives,
			HashMap<String, Integer> negatives) {
		int totPos = 0;
		for (Example ex : examples) {
			int i = 1;
			String value = ex.getValue(attr);
			HashMap<String, Integer> tempMap;
			if (ex.getGoal().getClassification()) {
				tempMap = positives;
				totPos++;
			} else {
				tempMap = negatives;
			}
			String key = attr.getKeyIfNumerical(value);
			if (tempMap.containsKey(key)) {
				i = tempMap.get(key);
				i++;
			}
			tempMap.put(key, i);
		}
		return totPos;
	}
}
