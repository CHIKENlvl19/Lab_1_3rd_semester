use std::env;
use std::fs::{File, OpenOptions};
use std::io::{self, BufRead, BufReader, Write};
use std::process;

#[derive(Debug, Clone)]
struct MyArray {
    data: Vec<String>,
}

impl MyArray {
    fn new() -> Self {
        MyArray { data: Vec::new() }
    }

    fn load_from_file(filename: &str) -> Self {
        if let Ok(file) = File::open(filename) {
            let reader = BufReader::new(file);
            let mut arr = MyArray::new();
            for line in reader.lines() {
                if let Ok(l) = line {
                    arr.data.push(l);
                }
            }
            arr
        } else {
            MyArray::new()
        }
    }

    fn save_to_file(&self, filename: &str) {
    if let Some(parent) = std::path::Path::new(filename).parent() {
        std::fs::create_dir_all(parent).unwrap();
    }

    let mut file = File::create(filename)
        .unwrap_or_else(|_| panic!("Cannot open array file for writing: {}", filename));
        for item in &self.data {
            writeln!(file, "{}", item).unwrap();
        }
    }


    fn push_back(&mut self, value: String, filename: &str) {
        self.data.push(value);
        self.save_to_file(filename);
    }

    fn insert(&mut self, index: usize, value: String, filename: &str) {
        if index > self.data.len() {
            panic!("Error: inserting failed due to invalid index.");
        }
        self.data.insert(index, value);
        self.save_to_file(filename);
    }

    fn delete(&mut self, index: usize, filename: &str) {
        if index >= self.data.len() {
            panic!("Error: deleting failed due to invalid index.");
        }
        self.data.remove(index);
        self.save_to_file(filename);
    }

    fn swap(&mut self, index: usize, value: String, filename: &str) {
        if index >= self.data.len() {
            panic!("Error: swapping an element failed due to invalid index.");
        }
        self.data[index] = value;
        self.save_to_file(filename);
    }

    fn get(&self, index: usize) -> String {
        if index >= self.data.len() {
            panic!("Error: getting an element failed due to invalid index.");
        }
        self.data[index].clone()
    }

    fn print(&self) {
        print!("[");
        for (i, item) in self.data.iter().enumerate() {
            print!("{}", item);
            if i < self.data.len() - 1 {
                print!(", ");
            }
        }
        println!("]");
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() < 4 {
        eprintln!("Usage: ./array_bin --file file.data --query 'CMD ...'");
        process::exit(1);
    }

    let mut filename = String::new();
    let mut query = String::new();

    let mut i = 1;
    while i < args.len() {
        match args[i].as_str() {
            "--file" if i + 1 < args.len() => {
                filename = args[i + 1].clone();
                i += 1;
            }
            "--query" if i + 1 < args.len() => {
                query = args[i + 1].clone();
                i += 1;
            }
            _ => {}
        }
        i += 1;
    }

    if filename.is_empty() || query.is_empty() {
        eprintln!("Error: --file and --query are required");
        process::exit(1);
    }

    let mut parts = query.split_whitespace();
    let cmd = parts.next().unwrap_or("");

    let mut arr = MyArray::load_from_file(&filename);

    match cmd {
        "APUSH" => {
            if let Some(value) = parts.next() {
                arr.push_back(value.to_string(), &filename);
            }
        }
        "AINSERT" => {
            if let (Some(idx), Some(value)) = (parts.next(), parts.next()) {
                let index: usize = idx.parse().unwrap();
                arr.insert(index, value.to_string(), &filename);
            }
        }
        "ADELETE" => {
            if let Some(idx) = parts.next() {
                let index: usize = idx.parse().unwrap();
                arr.delete(index, &filename);
            }
        }
        "ASWAP" => {
            if let (Some(idx), Some(value)) = (parts.next(), parts.next()) {
                let index: usize = idx.parse().unwrap();
                arr.swap(index, value.to_string(), &filename);
            }
        }
        "AGET" => {
            if let Some(idx) = parts.next() {
                let index: usize = idx.parse().unwrap();
                println!("{}", arr.get(index));
            }
        }
        "APRINT" => {
            arr.print();
        }
        _ => {
            eprintln!("Unknown command: {}", cmd);
            process::exit(1);
        }
    }
}
