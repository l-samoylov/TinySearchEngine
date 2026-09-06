# Tiny Search Engine

Tiny Search Engine is a three-part program that crawls a website, builds a searchable index, and returns ranked results for text queries.

## Crawler

The crawler starts at a given `seedURL`. It downloads and saves that page, finds links within it, and adds new internal links to its collection of pages to visit. It ignores external and previously seen links, which prevents it from leaving the target website or repeatedly following cycles. This continues until there are no pages left to visit within the chosen maximum depth.

## Indexer

The indexer reads each saved page and extracts its words. It ignores words shorter than three letters, converts the remaining words to lowercase, and records how often each word appears on each page. It then saves this information as an index for later searches.

## Querier

The querier loads the saved index and repeatedly accepts search queries. It normalizes and validates each query, then finds and scores matching pages. Words joined by `and` must appear together, while groups separated by `or` are combined; `and` is evaluated before `or`. Matching pages are displayed from highest to lowest score with their web addresses.

## Search Pipeline

The crawler gathers pages, the indexer turns those pages into a word-frequency index, and the querier uses that index to rank search results.

## Author

Lisa Samoylov
