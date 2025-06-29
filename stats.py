import subprocess
import re
from collections import defaultdict
from datetime import datetime
import argparse

def list_solved_problems_by_month(year):
    # Get commits in chronological order
    cmd = [
        'git', 'log',
        '--reverse',
        '--pretty=format:%ad|%s',
        '--date=short'
    ]
    result = subprocess.run(cmd, capture_output=True, text=True)
    lines = result.stdout.strip().split('\n')

    pattern = re.compile(r'^(\d{4}-\d{2}-\d{2})\|([\w-]+): Solve "(.+)"$')

    seen = set()
    problems_by_month = defaultdict(list)

    for line in lines:
        match = pattern.match(line)
        if not match:
            continue

        date, site, title = match.groups()
        if not date.startswith(str(year)):
            continue

        key = f"{site.lower()}::{title.lower()}"
        if key in seen:
            continue

        seen.add(key)
        month = date[:7]
        problems_by_month[month].append((site, title))

    # Output
    total = sum(len(v) for v in problems_by_month.values())
    print(f"\n🧮 Total unique problems solved in {year}: {total}\n")

    for month in sorted(problems_by_month):
        print(f"📅 {month}")
        for site, title in problems_by_month[month]:
            print(f"   • [{site}] {title}")
        print()

    return problems_by_month

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="List solved problems by month from Git commits.")
    parser.add_argument(
        'year',
        nargs='?',
        default=datetime.now().year,
        type=int,
        help='Year to analyze (default: current year)'
    )
    args = parser.parse_args()
    list_solved_problems_by_month(args.year)
