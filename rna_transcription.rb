# Takes a DNA or RNA strand and transcribes it to its counterpart by replacing
# each nucleotide with its complement. Not for use in actual science. View on
# Exercism: http://exercism.io/submissions/a94b9bb489cf4061ab9eee0809c66553

class Complement
  VERSION = 2
  @@dna_rna = { 'G' => 'C', 'C' => 'G', 'T' => 'A', 'A' => 'U' }

  def self.of_dna(dna); complementor(dna, @@dna_rna); end
  def self.of_rna(rna); complementor(rna, @@dna_rna.invert); end

  private
  def self.complementor(strand, map)
    strand.chars.map do |nt|
      raise ArgumentError unless map.include?(nt)
      map[nt]
    end.join
  end
end
