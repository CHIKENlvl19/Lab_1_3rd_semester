use std::env;
use std::fs::{File, OpenOptions};
use std::io::{self, BufRead, BufReader, Write};
use std::path::Path;

#[derive(Clone)]
struct DLList {
    data: Vec<String>, // просто храним элементы в векторе
}

impl DLList {
    fn new() -> Self {
        DLList { data: Vec::new() }
    }

    fn load_from_file(filename: &str) -> Self {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let lines: Vec<String> = reader.lines().filter_map(Result::ok).collect();
            DLList { data: lines }
        } else {
            DLList::new()
        }
    }

    fn save_to_file(&self, filename: &str) {
        if let Some(parent) = Path::new(filename).parent() {
            std::fs::create_dir_all(parent).unwrap();
        }

        let mut file = File::create(filename)
            .unwrap_or_else(|_| panic!("Cannot open DLList file for writing: {}", filename));

        for value in &self.data {
            writeln!(file, "{}", value).unwrap();
        }
    }

    fn add_head(&mut self, value: String, filename: &str) {
        self.data.insert(0, value);
        self.save_to_file(filename);
    }

    fn add_tail(&mut self, value: String, filename: &str) {
        self.data.push(value);
        self.save_to_file(filename);
    }

    fn remove_head(&mut self, filename: &str) {
        if !self.data.is_empty() {
            self.data.remove(0);
        }
        self.save_to_file(filename);
    }

    fn remove_tail(&mut self, filename: &str) {
        if !self.data.is_empty() {
            self.data.pop();
        }
        self.save_to_file(filename);
    }

    fn search(&self, value: &str) -> i32 {
        for (i, v) in self.data.iter().enumerate() {
            if v == value {
                return i as i32;
            }
        }
        -1
    }

    fn print(&self) {
        if self.data.is_empty() {
            println!("[]");
            return;
        }
        print!("[");
        for (i, v) in self.data.iter().enumerate() {
            if i > 0 {
                print!(" <-> ");
            }
            print!("{}", v);
        }
        println!("]");
    }

    fn print_backwards(&self) {
        if self.data.is_empty() {
            println!("[]");
            return;
        }
        print!("[");
        for (i, v) in self.data.iter().rev().enumerate() {
            if i > 0 {
                print!(" <-> ");
            }
            print!("{}", v);
        }
        println!("]");
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 5 {
        eprintln!("Usage: {} --file <filename> --query <command>", args[0]);
        return;
    }

    let filename = args[2].clone();
    let query = args[4].clone();
    let mut list = DLList::load_from_file(&filename);

    let parts: Vec<&str> = query.split_whitespace().collect();
    match parts[0] {
        "DLADDHEAD" => {
            if parts.len() < 2 {
                eprintln!("Error: DLADDHEAD requires a value");
                return;
            }
            list.add_head(parts[1].to_string(), &filename);
        }
        "DLADDTAIL" => {
            if parts.len() < 2 {
                eprintln!("Error: DLADDTAIL requires a value");
                return;
            }
            list.add_tail(parts[1].to_string(), &filename);
        }
        "DLDELHEAD" => {
            list.remove_head(&filename);
        }
        "DLDELTAIL" => {
            list.remove_tail(&filename);
        }
        "DLSEARCH" => {
            if parts.len() < 2 {
                eprintln!("Error: DLSEARCH requires a value");
                return;
            }
            let idx = list.search(parts[1]);
            if idx >= 0 {
                println!("Found at index {}", idx);
            } else {
                println!("Not found");
            }
        }
        "DLPRINT" => {
            list.print();
        }
        "DLPRINTBACK" => {
            list.print_backwards();
        }
        _ => {
            eprintln!("Unknown command: {}", parts[0]);
        }
    }
}
