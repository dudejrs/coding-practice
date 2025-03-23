package com.example.design_pattern;

import java.util.*;

public class Facade {

  private static class Facade_ {

    private static class File {
      private String name;

      File(String name) {
        this.name = name;
      }

      void write(String buffer) {}

      void save() {}
    }

    private static class VideoFile extends File {
      private String format;

      VideoFile(String name, String format) {
        super(name);
        this.format = format;
      }

      public String format() {
        return format;
      }
    }

    private static class VideoFiles {
      private VideoFiles() {}

      public static VideoFile get(String name) {
        String[] tokens = name.split("\\.");
        return new VideoFile(tokens[0], tokens[1]);
      }
    }

    private static interface Codec {}

    private static class MPEG4Codec implements Codec {}

    private static class OGGCodec implements Codec {}

    private static class CodecFactory {

      private CodecFactory() {}

      private static Codec extract(VideoFile file) {
        if ("mp4".equals(file.format())) {
          return new MPEG4Codec();
        }
        return new OGGCodec();
      }

      private static Codec get(String format) {
        if ("mp4".equals(format)) {
          return new MPEG4Codec();
        }
        return new OGGCodec();
      }
    }

    private static class BitrateReader {
      public static String read(File file, Codec codec) {
        return "";
      }

      public static String convert(String buffer, Codec codec) {
        return "";
      }
    }

    private static class VideoConverter {
      VideoFile convert(String filename, String format) {
        VideoFile file = VideoFiles.get(filename);
        Codec srcCodec = CodecFactory.extract(file);
        Codec dstCodec = CodecFactory.get(format);

        String buffer = BitrateReader.read(file, srcCodec);
        String result = BitrateReader.convert(buffer, dstCodec);
        file.write(result);
        return file;
      }
    }

    public static void main() {
      VideoConverter converter = new VideoConverter();
      VideoFile file = converter.convert("test.ogg", "mp4");
      file.save();
    }
  }

  public static void main(String... args) {
    Facade_.main();
  }
}
