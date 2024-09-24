// Problem: https://codeforces.com/contest/1354/problem/D
// Submission: https://codeforces.com/contest/1354/submission/282803376
// Status: Accepted

use core::panic;
use std::{
    io::{self, Read},
    usize,
};

// Experimental prototype (WIP).
fn read_i32() -> io::Result<i32> {
    let mut stdin = io::stdin();
    let mut buffer = [0u8; 1];
    let mut number = 0;
    let whitespace = [b' ', b'\n', b'\t'];

    // Skip leading whitespace
    stdin.read_exact(&mut buffer)?;
    while whitespace.contains(&buffer[0]) {
        stdin.read_exact(&mut buffer)?;
    }

    // Determine the sign
    let sign = if buffer[0] == b'-' {
        stdin.read_exact(&mut buffer)?;
        -1
    } else {
        1
    };

    // Read and process digits
    while b'0' <= buffer[0] && buffer[0] <= b'9' {
        let digit = (buffer[0] - b'0') as i32;
        number = number * 10 + digit;
        stdin.read_exact(&mut buffer)?
    }
    number *= sign;
    Ok(number)
}

struct FenwickTree {
    bit: Vec<u32>,
    n: usize,
    max_p2: usize,
}

impl FenwickTree {
    // Fenwick tree helper functions. This implementation uses 0-based indexing.
    // Ranges will be [g(i), i].
    // g(i) <= i
    #[allow(dead_code)]
    fn g(i: usize) -> usize {
        i & (i + 1)
    }
    // h(j) is used to propagate updates in the tree.
    // h(j) > j
    fn h(j: usize) -> usize {
        j | (j + 1)
    }

    // Constructor similar to String::from().
    fn from(v: Vec<u32>) -> Self {
        let n = v.len() - 1;
        let mut fen = FenwickTree {
            bit: v,
            n,
            max_p2: 1 << (std::mem::size_of::<usize>() * 8 - n.leading_zeros() as usize),
        };

        let bit = &mut fen.bit;
        for i in 0..=n {
            if FenwickTree::h(i) <= n {
                bit[FenwickTree::h(i)] += bit[i];
            }
        }

        fen
    }

    fn process_queries(&mut self, q: u32) -> io::Result<()> {
        for _ in 0..q {
            self.query(read_i32()?)
        }
        Ok(())
    }

    fn query(&mut self, k: i32) {
        if k >= 0 {
            self.update(k as usize, 1); // insert k
        } else {
            self.update(
                // remove k'th order statistic
                match self.find_statistic(-k as u32) {
                    Some(k) => k as usize,
                    None => panic!("empty"),
                },
                -1,
            );
        }
    }

    fn update(&mut self, mut k: usize, delta: i8) {
        let bit = &mut self.bit;
        while k <= self.n {
            bit[k] = (bit[k] as i32 + delta as i32) as u32;
            k = FenwickTree::h(k);
        }
    }

    // The k'th order statistic.
    fn find_statistic(&self, mut k: u32) -> Option<usize> {
        let bit = &self.bit;
        let mut pos: usize = 0;
        let mut interval = self.max_p2;
        while interval > 0 {
            if (pos + interval - 1) <= self.n && bit[(pos + interval - 1) as usize] < k {
                k -= bit[(pos + interval - 1) as usize];
                pos += interval;
            }
            interval /= 2;
        }
        if pos <= self.n {
            Some(pos)
        } else {
            None
        }
    }

    fn get_first(&self) -> Option<usize> {
        let pos = self.find_statistic(1)?;
        Some(pos)
    }
}

fn read_frequency_vector(v: &mut Vec<u32>) {
    let n = v.len() - 1;
    for _ in 0..n {
        let elem = match read_i32() {
            Ok(e) => e,
            Err(_) => panic!("IO error"),
        };
        v[elem as usize] += 1;
    }
}

fn main() {
    let (n, q) = match (read_i32(), read_i32()) {
        (Ok(x), Ok(y)) => (x as usize, y as u32),
        (_, _) => panic!("IO error"),
    };
    let mut v: Vec<u32> = vec![0; n + 1];
    read_frequency_vector(&mut v);
    let mut bit = FenwickTree::from(v);

    if let Err(_) = bit.process_queries(q) {
        panic!("IO error");
    }
    println!(
        "{}",
        match bit.get_first() {
            Some(pos) => pos,
            None => 0,
        }
    );
}
