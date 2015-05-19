package decision_trees;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Scanner;

public class DecisionTreeParser {
	private Relation rel;

	public DecisionTreeParser(File file, String positiveClass) {
		Scanner scan = null;
		try {
			scan = new Scanner(new BufferedReader(new FileReader(file)));
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		LinkedList<String> lines = new LinkedList<String>();
		while (scan.hasNextLine()) {
			String line = scan.nextLine();
			if (!line.startsWith("%") && !line.isEmpty()) {
				lines.addLast(line.toLowerCase());
			}
		}
		ArrayList<Attribute> attributes = null;
		ArrayList<Example> examples = null;
		String relation = null;
		while (!lines.isEmpty()) {
			String line = lines.removeFirst();
			String[] elements = line.split(" ");
			if (elements[0].equals("@relation")) {
				relation = elements[1];
				attributes = new ArrayList<Attribute>();
				examples = new ArrayList<Example>();
			} else if (elements[0].equals("@attribute")) {
				HashSet<String> values = new HashSet<String>();
				if (elements[2].equals("real") || elements[2].equals("numeric")
						|| elements[2].equals("integer")) {
					values.add("%numeric");
					attributes.add(new Attribute(elements[1], values));
				} else if (elements[2].equals("string")) {
					System.err.println("String not supported!");
					System.exit(1);
				} else if (elements[2].equals("date")) {
					System.err.println("Date not supported!");
					System.exit(1);
				} else if (elements[2].startsWith("{")) {
					String[] stringValues = line.substring(
							line.indexOf('{') + 1, line.indexOf('}'))
							.split(",");
					for (String value : stringValues) {
						values.add(value.trim());
					}
					attributes.add(new Attribute(elements[1], values));
				} else {
					System.err.println("Type not supported!");
					System.exit(1);
				}
			} else if (elements[0].equals("@data")) {
				while (!lines.isEmpty()
						&& !lines.peekFirst().startsWith("@relation")
						&& !lines.peekFirst().startsWith("@data")) {
					String[] example = lines.removeFirst().split(",");
					HashMap<Attribute, String> ex = new HashMap<Attribute, String>();
					for (int i = 0; i < example.length - 1; i++) {
						Attribute a = attributes.get(i);
						String value = example[i];
						if (!a.validValue(value)) {
							System.err.println("Value not defined!");
							System.exit(1);
						}
						ex.put(a, value);
					}
					Attribute a = attributes.get(example.length - 1);
					String value = example[example.length - 1];
					if (!a.validValue(value)) {
						System.err.println("Value not defined!");
						System.exit(1);
					}
					Goal goal = new Goal(a, value, value.equals(positiveClass));
					examples.add(new Example(ex, goal));
				}
			}
		}
		attributes.remove(attributes.size() - 1);
		rel = new Relation(relation, attributes, examples);
	}

	public Relation getRelation() {
		return rel;
	}
}
