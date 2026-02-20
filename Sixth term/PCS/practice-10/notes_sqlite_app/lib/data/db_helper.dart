import 'dart:async';
import 'package:path/path.dart' as p;
import 'package:path_provider/path_provider.dart';
import 'package:sqflite/sqflite.dart';
import '../models/note.dart';

class DBHelper {
  static const _dbName = 'app.db';
  static const _dbVersion = 2; // если хотите включить миграцию — поставьте 2
  static Database? _db;

  static const notesTable = 'notes';

  static Future<Database> _open() async {
    if (_db != null) return _db!;
    final docs = await getApplicationDocumentsDirectory();
    final dbPath = p.join(docs.path, _dbName);

    _db = await openDatabase(
      dbPath,
      version: _dbVersion,
      onCreate: (db, version) async {
        await db.execute('''
          CREATE TABLE $notesTable(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            body TEXT NOT NULL,
            created_at INTEGER NOT NULL,
            updated_at INTEGER NOT NULL,
            is_favorite INTEGER NOT NULL DEFAULT 0
          );
        ''');
        await db.execute('CREATE INDEX idx_notes_created_at ON $notesTable(created_at DESC);');
        await db.execute('CREATE INDEX idx_notes_favorite ON $notesTable(is_favorite);');
        await db.execute('PRAGMA foreign_keys = ON;');
        await db.execute('PRAGMA journal_mode = WAL;');
      },
      onUpgrade: (db, oldV, newV) async {
        if (oldV < 2) {
          await db.execute('ALTER TABLE $notesTable ADD COLUMN is_favorite INTEGER NOT NULL DEFAULT 0;');
          await db.execute('CREATE INDEX IF NOT EXISTS idx_notes_favorite ON $notesTable(is_favorite);');
        }
      },
    );

    return _db!;
  }

  // CREATE
  static Future<int> insertNote(Note note) async {
    final db = await _open();
    return db.insert(notesTable, note.toMap(), conflictAlgorithm: ConflictAlgorithm.abort);
  }

  // READ all
  static Future<List<Note>> fetchNotes({int limit = 100, int offset = 0}) async {
    final db = await _open();
    final rows = await db.query(
      notesTable,
      orderBy: 'created_at DESC',
      limit: limit,
      offset: offset,
    );
    return rows.map((m) => Note.fromMap(m)).toList();
  }

  // READ by id
  static Future<Note?> fetchNoteById(int id) async {
    final db = await _open();
    final rows = await db.query(notesTable, where: 'id = ?', whereArgs: [id], limit: 1);
    if (rows.isEmpty) return null;
    return Note.fromMap(rows.first);
  }

  // UPDATE
  static Future<int> updateNote(Note note) async {
    final db = await _open();
    return db.update(
      notesTable,
      note.toMap(),
      where: 'id = ?',
      whereArgs: [note.id],
      conflictAlgorithm: ConflictAlgorithm.abort,
    );
  }

  // DELETE
  static Future<int> deleteNote(int id) async {
    final db = await _open();
    return db.delete(notesTable, where: 'id = ?', whereArgs: [id]);
  }

  // SEARCH
  static Future<List<Note>> searchByTitle(String q) async {
    final db = await _open();
    final rows = await db.query(
      notesTable,
      where: 'title LIKE ?',
      whereArgs: ['%$q%'],
      orderBy: 'created_at DESC',
    );
    return rows.map((m) => Note.fromMap(m)).toList();
  }

  // Close DB
  static Future<void> close() async {
    if (_db != null) {
      await _db!.close();
      _db = null;
    }
  }
}
