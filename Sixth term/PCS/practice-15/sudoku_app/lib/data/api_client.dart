import 'dart:convert';
import 'package:http/http.dart' as http;

class ApiClient {
  final String baseUrl;

  ApiClient({required this.baseUrl});

  Future<List<dynamic>> getList(String endpoint) async {
    final url = Uri.parse('$baseUrl/$endpoint?sortBy=time&order=asc');
    final res = await http.get(url);
    if (res.statusCode != 200) throw Exception('API Error');
    return jsonDecode(res.body);
  }

  Future<Map<String, dynamic>> post(
      String endpoint, Map<String, dynamic> data) async {
    final url = Uri.parse('$baseUrl/$endpoint');
    final res = await http.post(
      url,
      body: jsonEncode(data),
      headers: {'Content-Type': 'application/json'},
    );
    if (res.statusCode != 201) throw Exception('POST error');
    return jsonDecode(res.body);
  }
}
