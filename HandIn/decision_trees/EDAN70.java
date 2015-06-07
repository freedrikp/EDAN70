package decision_trees;

import java.io.File;
import java.util.Scanner;

public class EDAN70 {

	public static void main(String[] args) {
		DecisionTreeParser dtp = new DecisionTreeParser(new File(args[0]),
				args[1]);
		Relation rel = dtp.getRelation();
		DecisionTreeAlgorithm dta = new DecisionTreeAlgorithm(rel);

		for (Attribute attr : rel.getAttributes()) {
			ArrayList<Pair> list = new ArrayList<Pair>();
			for (Example exam : rel.getExamples()) {
				Goal goal = exam.getGoal();
				Pair p = new Pair(Double.parseDouble(exam.getValue(attr)),
						goal.getClassification());
				list.add(p);
			}
			Collections.sort(list);
			double bestSplit = -1;
			double info = -1;
			Pair prev = list.get(0);
			for (Pair curr : list) {

				if (prev.getClassification() != curr.getClassification()) {

					double currentSplit = (prev.getValue() + curr.getValue()) / 2;

					attr.setSplitPoint(currentSplit);

					double temp = dta.calculateGain(attr, rel.getExamples());

					if (temp > info) {
						bestSplit = currentSplit;
						info = temp;
					}
				}
				prev = curr;
			}
			attr.setSplitPoint(bestSplit);
		}

		DecisionNode node = dta.dtl();
		if (args.length >= 3 && args[2].equals("prune")) {
			node = dta.pruning(node);
		}
		System.out.println(node.print(0));
	}

}
