use std::env;
use std::fs::{File, OpenOptions};
use std::io::{self, BufRead, BufReader, Write};
use std::path::Path;

const MAX_STACK_SIZE: usize = 1000;

#[derive(Clone)]
struct Stack {
    data: Vec<String>,
}

impl Stack {
    fn new() -> Self {
        Stack { data: Vec::new() }
    }

    fn load_from_file(filename: &str) -> Self {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let mut lines: Vec<String> = reader
                .lines()
                .filter_map(Result::ok)
                .collect();

            // данные в файле хранятся сверху вниз,
            // в вектор кладём "сверху стэка" — последний элемент
            lines.reverse();
            Stack { data: lines }
        } else {
            Stack::new()
        }
    }

    fn save_to_file(&self, filename: &str) {
        if let Some(parent) = Path::new(filename).parent() {
            std::fs::create_dir_all(parent).unwrap();
        }

        let mut file = File::create(filename)
            .unwrap_or_else(|_| panic!("Cannot open stack file for writing: {}", filename));

        // сохраняем сверху вниз (верх стэка — первая строка)
        for value in self.data.iter().rev() {
            writeln!(file, "{}", value).unwrap();
        }
    }

    fn push(&mut self, value: String, filename: &str) {
        if self.data.len() >= MAX_STACK_SIZE {
            panic!("Error: stack is full! Overflow might happen.");
        }
        self.data.push(value);
        self.save_to_file(filename);
    }

    fn pop(&mut self, filename: &str) {
        if self.data.is_empty() {
            panic!("Error: stack is empty! Nothing to delete.");
        }
        self.data.pop();
        self.save_to_file(filename);
    }

    fn print(&self) {
        if self.data.is_empty() {
            println!("Stack is empty!");
            return;
        }
        print!("nullptr");
        for val in self.data.iter().rev() {
            print!(" <- {}", val);
        }
        println!();
    }

    fn size(&self) -> usize {
        self.data.len()
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

    let mut stack = Stack::load_from_file(&filename);

    let parts: Vec<&str> = query.split_whitespace().collect();
    match parts[0] {
        "SPUSH" => {
            if parts.len() < 2 {
                eprintln!("Error: SPUSH requires a value");
                return;
            }
            stack.push(parts[1].to_string(), &filename);
        }
        "SPOP" => {
            stack.pop(&filename);
        }
        "SPRINT" => {
            stack.print();
        }
        _ => {
            eprintln!("Unknown command: {}", parts[0]);
        }
    }
}