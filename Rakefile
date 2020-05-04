PROJECT_HOME      = File.expand_path(File.dirname(__FILE__))
PROJECT_NAME      = "smart_home"
SRC_DIR           = "#{PROJECT_HOME}/src"
BUILD_DIR         = "#{PROJECT_HOME}/build"
SO_FILE_DIR      = "#{BUILD_DIR}/lib"
OBJ_FILES_DIR     = "#{BUILD_DIR}/objects"
SO_FILE_PATH     = "#{SO_FILE_DIR}/#{PROJECT_NAME}"
INCLUDE_DIRS      = %w(/opt/vc/include)
INCLUDE_OPTION    = INCLUDE_DIRS.map{|i_dir| "-I#{i_dir}"}.join(' ')
LIB_DIRS          = %w(/opt/vc/lib)
LIB_OPTIONS       = LIB_DIRS.map{|l_dir| "-L#{l_dir}"}.join(' ')
COMPILE_COMMANDS   = {
  cpp: ->(build_path, target_file) {
    "g++ -Wall -O0 -DNDEBUG -std=c++14 -lbcm_host #{LIB_OPTIONS} #{INCLUDE_OPTION} -o #{build_path}.o -c #{target_file}"
  }
}
LINK_COMMAND     = 'g++'
LINK_FLAGS       = "-shared -Wall -O0 -DNDEBUG -std=c++14 #{LIB_OPTIONS} -Wl,-rpath-link=#{LIB_DIRS} -lbcm_host"

task :default => ['build']

def get_match_files_recursion(path, &block)

  files = []

  Dir.each_child(path) do |f|

    file = "#{path}/#{f}"

    case File.ftype(file).to_sym
    when :directory
      files.concat(get_match_files_recursion(file, &block))
    when :file
      files << file if yield(file)
    else
    end
  end

  return files
end

desc "build to all"
task :build do |task, args|
  Rake::Task['build:clean'].execute
  Rake::Task['build:compile'].execute(args)
  Rake::Task['build:link'].execute
end

namespace :build do

  desc "compile"
  task :compile do |task, args|

    FileUtils.mkdir_p(OBJ_FILES_DIR) unless Dir.exists?(OBJ_FILES_DIR)

    COMPILE_COMMANDS.each do |suffix, command|
      func = ->(f){ File.fnmatch("*.#{suffix}", f) }
      target_files = get_match_files_recursion(SRC_DIR, &func)

      if args['all'].nil? || !!!args['all']
        #todo timestamp で差分のみ
      end

      target_files.each do |target|
        basename = File.basename(target, ".#{suffix}")
        sh command.call("#{OBJ_FILES_DIR}/#{basename}", target)
      end
    end
  end

  desc "link"
  task :link do
    FileUtils.mkdir_p(SO_FILE_DIR) unless Dir.exists?(SO_FILE_DIR)
    obj_files = get_match_files_recursion(OBJ_FILES_DIR){|f| File.fnmatch("*.o", f)}.join(' ')
    sh "#{LINK_COMMAND} #{LINK_FLAGS} -o #{SO_FILE_PATH} #{obj_files}"
  end

  desc "rm build dir"
  task :clean do
    sh "rm -r #{BUILD_DIR}" if Dir.exists?(BUILD_DIR)
  end
end
