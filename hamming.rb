# Find the Hamming distance between two DNA strands (or, to be more precise,
# their string representations). Not for use in actual science. View on
# Exercism: http://exercism.io/submissions/7bd6a1b609fc4f7dac0be5dfe177dae2

class Hamming
  VERSION = 1

  def self.compute(strand_one, strand_two)
    raise ArgumentError if strand_one.length != strand_two.length

    differences = []
    strand_one.chars.each.with_index do |nt, index|
      differences << strand_two[index] unless strand_two[index] == nt
    end

    differences.length
  end
end
