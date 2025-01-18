
static OPERATORS: &str = "+-*";

trait ContainsAny {
	fn contains_any(&self, substring: &str) -> bool;
}

impl ContainsAny for &str {
	fn contains_any(&self, substring: &str) -> bool {
		for c in substring.chars() {
			if self.contains(c) {
				return true
			}
		}	
		false
	}
}

fn compute(left: &Vec<i32>, right: &Vec<i32>, operator: &char) -> Vec<i32> {
	
	let mut results = vec![];

	for l in left {
		for r in right {
			let result = match *operator {
				'+' => l + r,
				'-' => l - r,
				'*' => l * r,
				_ => continue
			};

			results.push(result);
		}
	}

	results
}

pub fn solve(exp: &str) -> Vec<i32> {
	if !exp.contains_any(&OPERATORS) {

		let m = exp.parse().unwrap();

		return vec![m]
	}

	let mut results = vec![];

	for (i, c) in exp.chars().enumerate() {
		if OPERATORS.contains(c) {
			let left = solve(&exp[0..i]);
			let right = solve(&exp[i+1..]);
			
			results.extend(compute(&left, &right, &c))
		} 
	} 

	results
}

#[cfg(test)]
mod tests {
	use super::*;
	use std::fs::File;
	use std::io::{BufRead, BufReader};
	use util:: *;

	#[test]
	fn accuracy_test() {
		let file_path = get_data_path(env!("CARGO_MANIFEST_DIR"), "괄호를_삽입하는_여러가지_방법.txt");
		let file = File::open(file_path).unwrap();
		let mut reader = BufReader::new(file);

		let testcases = get_number_of_testcases(&mut reader);

		let mut line = String::new();

		for _ in 0..testcases {

			reader.read_line(&mut line)
				.expect("no more lines!");

			let expression = String::from(line.trim());
			line.clear();

			reader.read_line(&mut line)
				.expect("no more lines");
			println!("");
			
				
			let mut answer : Vec<i32> = line.trim()
							.split_whitespace()
							.filter_map(|s| s.parse().ok())
							.collect();
			line.clear();

			let mut solved = solve(&expression);

			answer.sort();
			solved.sort();

			assert_eq!(solved, answer);
		}
	}
}