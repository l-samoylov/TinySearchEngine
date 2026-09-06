# Tiny Search Engine

Tiny Search Engine is a three-part program that crawls a website, builds a searchable index, and returns ranked results for text queries.

## Crawler

The crawler starts at a given `seedURL`. It downloads and saves that page, finds links within it, and adds new internal links to its collection of pages to visit. It ignores external and previously seen links, which prevents it from leaving the target website or repeatedly following cycles. This continues until there are no pages left to visit within the chosen maximum depth.

## Indexer

The indexer reads each saved page and extracts its words. It ignores words shorter than three letters, converts the remaining words to lowercase, and records how often each word appears on each page. It then saves this information as an index for later searches.

## Querier

The querier loads the saved index and repeatedly accepts search queries. It normalizes and validates each query, then finds and scores matching pages. Words joined by `and` must appear together, while groups separated by `or` are combined; `and` is evaluated before `or`. Matching pages are displayed from highest to lowest score with their web addresses.

## Build and Run

Run these commands from the directory containing the main Makefile. The project requires GCC, Make, and a Linux-style shell such as Linux, WSL, or Git Bash.

First, build all three programs and prepare empty output locations. Use a new or empty page directory for each crawl; the index file must also exist before the indexer runs.

```bash
make
mkdir -p data/pages
touch data/index
```

Run the crawler with a `seedURL`, the page destination, and a maximum depth from 0 through 10:

```bash
./crawler/crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ data/pages 2
```

Crawler output shows which pages are fetched, scanned, added, or ignored:

```text
 0   Fetched: http://cs50tse.cs.dartmouth.edu/tse/letters/
 0  Scanning: http://cs50tse.cs.dartmouth.edu/tse/letters/
 1     Found: http://cs50tse.cs.dartmouth.edu/tse/letters/A.html
 1     Added: http://cs50tse.cs.dartmouth.edu/tse/letters/A.html
```

Next, build the index from the saved pages:

```bash
./indexer/indexer data/pages data/index
```

Finally, start the querier with the saved pages and index:

```bash
./querier/querier data/pages data/index
```

Enter a query at the prompt. Adjacent words behave like `and`. Use `or` to combine groups of results:

```text
Query?: search and engine
Query: search and engine
Matched 2 documents:
score 4 doc 3: http://example.com/page-three
score 2 doc 7: http://example.com/page-seven
```

The displayed pages and scores depend on the crawled website. Press `Ctrl+D` to stop the querier.

## Search Pipeline

The crawler gathers pages, the indexer turns those pages into a word-frequency index, and the querier uses that index to rank search results.

## Author

Lisa Samoylov

