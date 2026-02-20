import 'dart:io';
import 'package:camera_app/theme/app_theme.dart';
import 'package:flutter/material.dart';
import 'package:image/image.dart' as img;
import 'package:image_picker/image_picker.dart';
import 'package:permission_handler/permission_handler.dart';
import 'package:path_provider/path_provider.dart';

void main() => runApp(const CameraApp());

class CameraApp extends StatelessWidget {
  const CameraApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Camera Demo',
      theme: AppTheme.darkTheme,
      home: const CameraPage(),
    );
  }
}

class CameraPage extends StatefulWidget {
  const CameraPage({super.key});

  @override
  State<CameraPage> createState() => _CameraPageState();
}

class _CameraPageState extends State<CameraPage> {
  File? _image;
  final picker = ImagePicker();

  Future<void> _checkPermissions() async {
    await Permission.camera.request();
    await Permission.photos.request();
  }

  Future<void> _getImage(ImageSource source) async {
    await _checkPermissions();
    final XFile? pickedFile = await picker.pickImage(source: source);
    if (pickedFile != null) {
      setState(() => _image = File(pickedFile.path));
    }
  }

  Future<void> _saveImage() async {
    if (_image == null) return;
    final dir = await getApplicationDocumentsDirectory();
    final newFile = await _image!.copy('${dir.path}/photo_${DateTime.now().millisecondsSinceEpoch}.jpg');
    ScaffoldMessenger.of(context)
        .showSnackBar(SnackBar(content: Text('Сохранено: ${newFile.path}')));
  }

  Future<void> _applyBlackWhite() async {
    if (_image == null) return;

    final bytes = await _image!.readAsBytes();
    final original = img.decodeImage(bytes);

    if (original == null) return;

    final bw = img.grayscale(original);
    final newBytes = img.encodeJpg(bw, quality: 100);

    final tempDir = await getTemporaryDirectory();
    final bwFile = File('${tempDir.path}/bw_${DateTime.now().millisecondsSinceEpoch}.jpg');
    await bwFile.writeAsBytes(newBytes);

    setState(() => _image = bwFile);

    ScaffoldMessenger.of(context)
        .showSnackBar(const SnackBar(content: Text('Применён чёрно-белый фильтр')));
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Работа с камерой')),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            _image == null
                ? const Text('Фото не выбрано')
                : Image.file(_image!, width: 250, height: 250, fit: BoxFit.cover),

            const SizedBox(height: 20),

            ElevatedButton.icon(
              onPressed: () => _getImage(ImageSource.camera),
              icon: const Icon(Icons.camera_alt),
              label: const Text('Сделать фото'),
            ),

            ElevatedButton.icon(
              onPressed: () => _getImage(ImageSource.gallery),
              icon: const Icon(Icons.image),
              label: const Text('Выбрать из галереи'),
            ),

            const SizedBox(height: 10),

            ElevatedButton.icon(
              onPressed: _applyBlackWhite,
              icon: const Icon(Icons.filter_b_and_w),
              label: const Text('Чёрно-белый фильтр'),
            ),

            const SizedBox(height: 10),

            ElevatedButton.icon(
              onPressed: _saveImage,
              icon: const Icon(Icons.save),
              label: const Text('Сохранить фото'),
            ),
          ],
        ),
      ),
    );
  }
}
