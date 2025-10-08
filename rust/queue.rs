use std::env;
use std::fs::{File, OpenOptions};
use std::io::{self, BufRead, BufReader, Write};
use std::path::Path;

const MAX_QUEUE_SIZE: usize = 1000;

#[derive(Clone)]
struct Queue {
    data: Vec<String>,
}

impl Queue {
    fn new() -> Self {
        Queue { data: Vec::new() }
    }

    fn load_from_file(filename: &str) -> Self {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let lines: Vec<String> = reader
                .lines()
                .filter_map(Result::ok)
                .collect();

            // порядок в файле — первый элемент сверху
            Queue { data: lines }
        } else {
            Queue::new()
        }
    }

    fn save_to_file(&self, filename: &str) {
        if let Some(parent) = Path::new(filename).parent() {
            std::fs::create_dir_all(parent).unwrap();
        }

        let mut file = File::create(filename)
            .unwrap_or_else(|_| panic!("Cannot open queue file for writing: {}", filename));

        for value in &self.data {
            writeln!(file, "{}", value).unwrap();
        }
    }

    fn push(&mut self, value: String, filename: &str) {
        if self.data.len() >= MAX_QUEUE_SIZE {
            panic!("Error: queue is full! Overflow might happen.");
        }
        self.data.push(value);
        self.save_to_file(filename);
    }

    fn pop(&mut self, filename: &str) {
        if self.data.is_empty() {
            panic!("Error: queue is empty! Nothing to delete.");
        }
        self.data.remove(0);
        self.save_to_file(filename);
    }

    fn print(&self) {
        if self.data.is_empty() {
            println!("Queue is empty!");
            return;
        }

        print!("FRONT");
        for val in &self.data {
            print!(" -> {}", val);
        }
        println!(" -> BACK");
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

    let mut queue = Queue::load_from_file(&filename);

    let parts: Vec<&str> = query.split_whitespace().collect();
    match parts[0] {
        "QPUSH" => {
            if parts.len() < 2 {
                eprintln!("Error: QPUSH requires a value");
                return;
            }
            queue.push(parts[1].to_string(), &filename);
        }
        "QPOP" => {
            queue.pop(&filename);
        }
        "QPRINT" => {
            queue.print();
        }
        _ => {
            eprintln!("Unknown command: {}", parts[0]);
        }
    }
}
