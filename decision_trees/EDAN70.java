package decision_trees;

import java.io.File;
import java.util.Scanner;

public class EDAN70 {

	public static void main(String[] args) {
		DecisionTreeParser dtp = new DecisionTreeParser(new File(args[0]),
				args[1]);
		Relation rel = dtp.getRelation();
		Scanner scan = new Scanner(System.in);
		for (int i = 0; i < rel.getAttributes().size(); i++) {
			Attribute attr = rel.getAttributes().get(i);
			if (!attr.getValues().contains("%numeric")){
				continue;
			}
			System.out.println("Input splitpoint for " + attr.toString() + ": ");
			attr.setSplitPoint(scan.nextDouble());
		}
		scan.close();
		System.out.println("Calculating...");
		DecisionTreeAlgorithm dta = new DecisionTreeAlgorithm(rel);
		DecisionNode node = dta.dtl();
		System.out.println("Finished!");
		if (args.length >= 3 && args[2].equals("prune")){
			System.out.println("Pruning...");
			node = dta.pruning(node);
			System.out.println("Finished!");
		}
		System.out.println(node.print(0));

	}

}
