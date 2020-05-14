PROJECT_HOME      = File.expand_path(File.dirname(__FILE__))
PROJECT_NAME      = "libgpio"
SRC_DIR           = "#{PROJECT_HOME}/src"
HPP_DIRS_DIR      = "#{PROJECT_HOME}/include"
SO_FILE_DIR       = "#{PROJECT_HOME}/lib"
SO_FILE           = "#{SO_FILE_DIR}/#{PROJECT_NAME}"
BUILD_DIR         = "#{PROJECT_HOME}/build"
OBJ_FILES_DIR     = "#{BUILD_DIR}/objects"
INCLUDE_DIRS      = %w(/opt/vc/include)
INCLUDE_OPTION    = INCLUDE_DIRS.map{|i_dir| "-I#{i_dir}"}.join(' ')
LIB_DIRS          = %w(/opt/vc/lib)
LIB_OPTIONS       = LIB_DIRS.map{|l_dir| "-L#{l_dir}"}.join(' ')
COMPILE_COMMANDS   = {
  cpp: ->(build_file, src) {
    #"/home/vagrant/projects/raspi/tools/arm-bcm2708/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++ -Wall -O0 -DNDEBUG -std=c++14 -lbcm_host #{LIB_OPTIONS} #{INCLUDE_OPTION} -o #{build_file}.o -c #{src}"
    "arm-linux-gnueabihf-g++ -Wall -O0 -DNDEBUG -std=c++14 -lbcm_host #{LIB_OPTIONS} #{INCLUDE_OPTION} -o #{build_file}.o -c #{src}"
  }
}
LINK_COMMAND     = ->(so_file, obj_files) {
  #"g++ -shared -Wall -O0 -DNDEBUG -std=c++14 #{LIB_OPTIONS} -Wl,-rpath-link=#{LIB_DIRS} -lbcm_host -o #{so_file}.so #{obj_files}"
  "arm-linux-gnueabihf-g++ -shared -Wall -O0 -DNDEBUG -std=c++14 #{LIB_OPTIONS} -Wl,-rpath-link=#{LIB_DIRS} -lbcm_host -o #{so_file}.so #{obj_files}"
}

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
    sh LINK_COMMAND.call(SO_FILE, obj_files)
  end

  desc "rm build dir"
  task :clean do
    sh "rm -r #{BUILD_DIR}" if Dir.exists?(BUILD_DIR)
  end
end

desc "install"
task :install do |task, args|
  prefix = args['prefix'] || '/usr/local/'
  FileUtils.mkdir_p("#{prefix}include/#{PROJECT_NAME}") unless Dir.exists?("#{prefix}include/#{PROJECT_NAME}")
  FileUtils.mkdir_p("#{prefix}lib/#{PROJECT_NAME}")     unless Dir.exists?("#{prefix}lib/#{PROJECT_NAME}")
  sh "cp #{HPP_DIRS_DIR}/* #{prefix}include/#{PROJECT_NAME}/"
  sh "cp #{SO_FILE_DIR}/*  #{prefix}lib/#{PROJECT_NAME}/"
end
