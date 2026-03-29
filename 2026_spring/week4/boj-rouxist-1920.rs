use std::{io::{self, Read}};

// 시간초과
fn binary_search(v: &[i32], val: i32) -> bool {
    let mut left = 0;
    let mut right = v.len();

    while left < right {
        let mid = (left + right) / 2;

        if v[mid] < val {
            left = mid + 1;
        } else if v[mid] > val {
            right = mid;
        } else {
            return true;
        }
    }

    false
}

fn main() {
    // read input
    let mut input = String::new();
    io::stdin().read_to_string(&mut input).unwrap();
    let mut lines = input.lines();
    
    let _: usize = lines.next().unwrap().parse().unwrap();

    // Main Script
    let line = lines.next().unwrap();
    let mut v: Vec<i32> = line.split_whitespace().map(|s| s.parse::<i32>().unwrap()).collect();
    
    v.sort();

    let _: usize = lines.next().unwrap().parse().unwrap();
    let line = lines.next().unwrap();
    let vals_to_find: Vec<i32> = line.split_whitespace().map(|s| s.parse::<i32>().unwrap()).collect();

    for val_to_find in vals_to_find {
        if binary_search(&v, val_to_find) {
            println!("{}", 1);
        } else {
            println!("{}", 0);
        }
    }
}