use std::fs::File;
use std::io::{BufRead, BufReader};

pub fn get_data_path(path: &str, file_name: &str) -> String {
   format!("{}/data/{}", path, file_name)
}

pub fn get_number_of_testcases(reader: &mut BufReader<File>) -> i32 {
    let mut line = String::new();
    
    reader.read_line(&mut line)
        .expect("no more lines!");   

    line.trim().parse().expect("")
}