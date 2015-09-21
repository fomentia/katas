# Find the exact time a gigasecond away from the given time (a Time object).
# Great for finding your gigasecond birthday. View on Exercism:
# http://exercism.io/submissions/8bf69c9aa043444184c93c93ca05a920

class Gigasecond
  VERSION = 1

  def self.from(time)
    time + (10**9)
  end
end
