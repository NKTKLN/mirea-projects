class Score {
  final String id;
  final String name;
  final int time;
  final String difficulty;

  Score({
    required this.id,
    required this.name,
    required this.time,
    required this.difficulty,
  });

  factory Score.fromJson(Map<String, dynamic> json) {
    return Score(
      id: json["id"],
      name: json["name"],
      time: json["time"],
      difficulty: json["difficulty"],
    );
  }
}
