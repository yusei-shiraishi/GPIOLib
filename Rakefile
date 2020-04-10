PROJECT_HOME      = File.expand_path(File.dirname(__FILE__))
PROJECT_NAME      = "smart_home"
SRC_DIR           = "#{PROJECT_HOME}/src"
BUILD_DIR         = "#{PROJECT_HOME}/build"
EXE_FILE_DIR      = "#{BUILD_DIR}/exe"
OBJ_FILES_DIR     = "#{BUILD_DIR}/objects"
EXE_FILE_PATH     = "#{EXE_FILE_DIR}/#{PROJECT_NAME}"
INCLUDE_DIRS      = %w(/usr/local/boost_1_72_0/ /opt/vc/include).map{|i_dir| "-I#{i_dir}"}.join(' ')
LIB_DIRS          = %w(/opt/vc/lib).map{|l_dir| "-L#{l_dir}"}.join(' ')
COMPILE_COMMANDS   = {
  cpp: ->(build_path, target_file) {
    #"/home/vagrant/projects/raspi/tools/arm-bcm2708/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++ -Wall -O0 -DNDEBUG -std=c++14 -lbcm_host #{INCLUDE_DIRS} -o #{build_path}.o -c #{target_file}"
    "g++ -Wall -O0 -DNDEBUG -std=c++14 -lbcm_host #{LIB_DIRS} #{INCLUDE_DIRS} -o #{build_path}.o -c #{target_file}"
  }
}
LINK_COMMAND     = 'g++'
#LINK_COMMAND     = '/home/vagrant/projects/raspi/tools/arm-bcm2708/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++'
LINK_FLAGS       = "-Wall -O0 -DNDEBUG -std=c++14 #{LIB_DIRS} -Wl,-rpath-link=/opt/vc/lib -lbcm_host"

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

desc "build exe file to all"
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
    FileUtils.mkdir_p(EXE_FILE_DIR) unless Dir.exists?(EXE_FILE_DIR)
    obj_files = get_match_files_recursion(OBJ_FILES_DIR){|f| File.fnmatch("*.o", f)}.join(' ')
    sh "#{LINK_COMMAND} #{LINK_FLAGS} -o #{EXE_FILE_PATH} #{obj_files}"
  end

  desc "rm build dir"
  task :clean do
    sh "rm -r #{BUILD_DIR}" if Dir.exists?(BUILD_DIR)
  end
end
