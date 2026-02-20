import 'api_client.dart';
import '../models/score.dart';

class LeaderboardRepository {
  final ApiClient client;

  LeaderboardRepository(this.client);

  Future<List<Score>> list() async {
    final raw = await client.getList("scores");
    return raw.map((e) => Score.fromJson(e)).toList();
  }

  Future<Score> create(String name, int time, String difficulty) async {
    final raw = await client.post("scores", {
      "name": name,
      "time": time,
      "difficulty": difficulty,
    });
    return Score.fromJson(raw);
  }
}
