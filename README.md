# Benford Analysis Project

The Benford Analysis project provides a tool for conducting Benford's Law analysis on numerical datasets. Benford's Law, also known as the First-Digit Law, states that in many naturally occurring sets of numerical data, the leading significant digit is likely to be small. Specifically, it predicts the frequency distribution of digits in many real-life sources of data, such as financial statements, population numbers, and scientific data.

## Usage

This project can be run by either entering numbers separated by spaces as input or by adding a file as an argument on the command prompt. The program then performs Benford's Law analysis on the provided dataset.

### Calculation Formulas

Benford's Law predicts the expected distribution of leading digits based on the logarithmic distribution:

\[ P(d) = \log_{10}(d + 1) - \log_{10}(d) \]

Where:
- \( P(d) \) is the probability of leading digit \( d \).
- \( \log_{10} \) denotes the base-10 logarithm.

### Benford Analysis Law

| Digit | Benford's Law (%) |
|-------|-------------------|
| 1     | 30.1              |
| 2     | 17.6              |
| 3     | 12.5              |
| 4     | 9.7               |
| 5     | 7.9               |
| 6     | 6.7               |
| 7     | 5.8               |
| 8     | 5.1               |
| 9     | 4.6               |

The table above presents the expected percentages of leading digits according to Benford's Law.

### Analysis Results

After performing the analysis, the program generates a report detailing the observed frequencies of leading digits in the dataset and compares them with the expected frequencies based on Benford's Law. The report includes the following statistical measures for each digit:
- Mean
- Mode
- Frequency
- Standard Deviation

Additionally, the report indicates whether the dataset conforms to Benford's Law or not, providing valuable insights into the integrity and reliability of numerical datasets. Visualizations showing the percentage of occurrence for each digit are also included in the report.

This project assists users in identifying potential anomalies or irregularities in numerical datasets, facilitating further investigation and analysis.

