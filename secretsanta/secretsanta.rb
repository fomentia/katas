# Assign secret santas from a collection of people. A great program for your
# holiday festivities.

require "minitest/autorun"
require "byebug"

class TestSecretSanta < Minitest::Test
  def setup
    @secretsanta = SecretSanta.new
    @valid_result = @secretsanta.choose(valid_people)
    @invalid_result = @secretsanta.choose(invalid_people)
  end

  def valid_people
    [
      {first_name: "Bruce", last_name: "Wayne",     email: "bruce@wayne.net"},
      {first_name: "Luke",  last_name: "Skywalker", email: "luke@thejedi.org"},
      {first_name: "Leia",  last_name: "Skywalker", email: "leia@therebellion.net"},
      {first_name: "James", last_name: "Kirk",      email: "james@theenterprise.com"},
    ]
  end

  def invalid_people
    [
      {first_name: "Bruce", last_name: "Wayne",     email: "bruce@wayne.net"},
      {first_name: "Luke",  last_name: "Skywalker", email: "luke@thejedi.org"},
      {first_name: "Leia",  last_name: "Skywalker", email: "leia@therebellion.net"},
      {first_name: "Leia",  last_name: "Skywalker", email: "leia@therebellion.net"},
      {first_name: "James", last_name: "Kirk",      email: "james@theenterprise.com"},
    ]
  end

  def test_everyone_has_a_secret_santa
    @valid_result.each do |person|
      refute_equal person[:secret_santa], nil
    end
  end

  def test_secret_santa_from_different_family
    @valid_result.each do |person|
      refute_equal person[:last_name], person[:secret_santa][:last_name]
    end
  end

  def test_no_one_has_the_same_secret_santa
    list = []
    @valid_result.each do |person|
      list << person[:secret_santa][:first_name]
    end

    assert_equal list.count, list.uniq.count, "Two people have the same secret santa"
  end

  def test_returns_impossible_for_invalid_people
    assert_equal @invalid_result, "That combination of people makes it impossible for everyone to have a secret santa given the current rules (no one of the same family may have each other as secret santas)."
  end

  def test_from_file_extracts_people_correctly
    @people_from_file = @secretsanta.from_file("people.txt")
    assert_equal @people_from_file, valid_people
  end

  def test_from_file_cannot_use_non_txt_files
    @people_from_file = @secretsanta.from_file("people.rb")
    assert_equal @people_from_file, "Please use a .txt file"
  end
end

class SecretSanta
  def choose(people)
    sorted_people = sort_by_family(people)
    return sorted_people if sorted_people.is_a? String
    taken = []

    sorted_people.each do |person|
      while person[:secret_santa].nil?
        target = people.sample
        person[:secret_santa] = {first_name: target[:first_name], last_name: target[:last_name]} unless person[:last_name] == target[:last_name] || taken.include?(target)

        unless person[:secret_santa].nil?
          taken << target
        end
      end
    end

    sorted_people
  end

  def sort_by_family(people)
    families = Hash.new

    people.each do |person|
      family_sym = person[:last_name].to_sym
      if families.has_key?(family_sym)
        families[family_sym] << person
      else
        families = families.merge({family_sym => [person]})
      end
    end

    longest = families.max_by { |k, v| v.length }
    families_sans_longest = families
    families_sans_longest = families_sans_longest.reject { |key, _| key == longest.first }
    if longest.last.length > families_sans_longest.values.flatten.length
      return "That combination of people makes it impossible for everyone to have a secret santa given the current rules (no one of the same family may have each other as secret santas)."
    end

    sorted = Hash[families.sort_by { |k, v| v.length }].to_a.reverse
    sorted.each { |x| x.delete(x.first) }
    sorted = sorted.flatten

    sorted
  end

  def from_file(file_path)
    return "Please use a .txt file" unless File.extname(file_path) == ".txt"
    people = []

    File.open(file_path) do |f|
      f.each_line do |line|
        line = line.split
        return "Please use a valid structure (first name <space> last name <space> email <newline>)" unless line.count == 3
        person_hash = Hash.new
        person_hash[:first_name] = line[0]
        person_hash[:last_name] = line[1]
        person_hash[:email] = line[2]
        people << person_hash
      end
    end

    people
  end

  def pretty(people)
    people.each do |person|
      puts "#{person[:first_name]} #{person[:last_name]} got #{person[:secret_santa][:first_name]} #{person[:secret_santa][:last_name]}"
    end
  end
end
