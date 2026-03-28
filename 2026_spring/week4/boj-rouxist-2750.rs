use std::{io::{self, Read}};

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();
    
    let n_elem: usize = lines.next().unwrap().parse().unwrap();


    // Main Script
    let mut v: Vec<i32> = Vec::new();

    for _ in 0..n_elem {
        let elem: i32 = lines.next().unwrap().parse().unwrap();
        v.push(elem);
    }
    
    v.sort();
    
    for elem in v {
        println!("{}", elem);
    }
}