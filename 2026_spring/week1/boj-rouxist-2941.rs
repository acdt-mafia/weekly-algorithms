use std::io;

fn main() {
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let bytes = s.trim().as_bytes();

    let mut cnt = 0;
    let mut i = 0;

    while i < bytes.len() {
        // check 3-letter combination
        if i + 2 < bytes.len() && &bytes[i..i+3] == b"dz=" {
            cnt += 1;
            i += 3;
            continue;
        }

        // check 2-letter combinations
        if i + 1 < bytes.len() {
            let pair = &bytes[i..i+2];
            if pair == b"c-" ||
               pair == b"c=" ||
               pair == b"d-" ||
               pair == b"lj" ||
               pair == b"nj" ||
               pair == b"s=" ||
               pair == b"z=" {
                cnt += 1;
                i += 2;
                continue;
            }
        }

        // single character
        cnt += 1;
        
        i += 1;
    }

    println!("{}", cnt);
}