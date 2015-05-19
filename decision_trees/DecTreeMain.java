package decision_trees;

import java.io.File;
import java.util.ArrayList;

public class DecTreeMain {

	public static void main(String[] args) {
		DecisionTreeParser dtp = new DecisionTreeParser(
				new File("arff18-3.txt"), "yes");
		DecisionTreeAlgorithm dta = new DecisionTreeAlgorithm(dtp.getRelation());
		;
		System.out.println(dta.pruning(dta.dtl()).print(0));

		dtp = new DecisionTreeParser(new File("weather.nominal.arff"), "yes");
		dta = new DecisionTreeAlgorithm(dtp.getRelation());
		System.out.println(dta.pruning(dta.dtl()).print(0));

		dtp = new DecisionTreeParser(new File("diabetes.arff"),
				"tested_positive");
		Relation rel = dtp.getRelation();
		ArrayList<Double> splitPoints = new ArrayList<Double>();
		splitPoints.add(3.8);
		splitPoints.add(120.9);
		splitPoints.add(69.1);
		splitPoints.add(20.5);
		splitPoints.add(79.8);
		splitPoints.add(32.0);
		splitPoints.add(0.5);
		splitPoints.add(33.2);
		for (int i = 0; i < rel.getAttributes().size(); i++) {
			rel.getAttributes().get(i).setSplitPoint(splitPoints.get(i));
		}
		dta = new DecisionTreeAlgorithm(rel);
		System.out.println(dta.pruning(dta.dtl()).print(0));
	}

}
