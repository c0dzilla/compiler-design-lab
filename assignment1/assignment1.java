package CompilerDesignLab;

import java.util.*;
import java.lang.*;
import java.io.*;

class Tokenizer {
	static String delimiter;
	static Map<String, String> m = new HashMap<String, String>();
	
	static String[] split(String s) {
		return s.split(delimiter);
	}
	
	static void generateMapping() {
		m.put("int", "keyword");
		m.put("bool", "keyword");
		m.put("double", "keyword");
		m.put("float", "keyword");
		m.put("+", "operator");
		m.put("-", "operator");
		m.put("*", "operator");
		m.put("/", "operator");
	}
	
	static String type(String s) {
		if (s.length() == 0) return "";
		if (m.containsKey(s)) {
			return m.get(s);
		}
		if (s.matches("-?\\d+(\\.\\d+)?")) {
			return "number";
		}
		return "identifier";
	}
	
	public static void main (String[] args) throws java.lang.Exception
	{
		delimiter = " |;";
		generateMapping();
		String code = "int a = b 8 int ;";
		String[] words = split(code);
		for (int i=0;i<words.length;i++) {
			String word = words[i];
			String type = type(word);
			if (type == "") {
				continue;
			}
			System.out.println(word + ": " + type);
		}
	}
}