import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class GeneralMessage {

	public static class GeneralMapper 
		extends Mapper<Object, Text, Text, IntWritable>{
    
    private final static IntWritable one = new IntWritable(1);
    private Text word = new Text();
    private String message;  
    public void setup(Context context
			   ) throws IOException, InterruptedException {

		Configuration conf = context.getConfiguration();
		message = conf.get("Message");
		}  
  
    public void map(Object key, Text value, Context context
                    ) throws IOException, InterruptedException {
		String itr = new String (value.toString());
		String[] arrOfitr = itr.split("\t");
		String user;
		String tweet;
		if (arrOfitr.length ==2) 
		{
			user = arrOfitr[0];
			tweet = arrOfitr[1];
			//Boolean found = false;
			int j=0;
			for (int i=0;i<tweet.length();i++) 
			{
				if (j<message.length()) 
				{
					if (tweet.charAt(i) == message.charAt(j)) 
					{
						j++;
					}
				}
			}
			if (j==message.length()) 
			{
				word.set(user);
				context.write(word, one);
			}
		}
    }
  }
  
  public static class GeneralReducer 
       extends Reducer<Text,IntWritable,Text,IntWritable> {
    private IntWritable result = new IntWritable();

    public void reduce(Text key, Iterable<IntWritable> values, 
                       Context context
                       ) throws IOException, InterruptedException {
		int sum=0;
		for (IntWritable val : values) 
		{
			sum += val.get();
		}
		result.set(sum);
		context.write(key, result);
    }
  }

public static void main(String[] args) throws Exception {
    Configuration conf = new Configuration();
    String[] otherArgs = new GenericOptionsParser(conf, args).getRemainingArgs();
    if (otherArgs.length != 3) 
	{
		System.err.println("Usage: generalmessage SEARCHSTRING <in> <out>");
		System.exit(2);
    }
	
    Job job = Job.getInstance();
    conf = job.getConfiguration();
		conf.set("Message", otherArgs[0]);
    job.setJobName("General Secret Message");
    job.setJarByClass(GeneralMessage.class);
    job.setMapperClass(GeneralMapper.class);
    job.setCombinerClass(GeneralReducer.class);
    job.setReducerClass(GeneralReducer.class);
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);
	
    FileInputFormat.addInputPath(job, new Path(otherArgs[1]));
    FileOutputFormat.setOutputPath(job, new Path(otherArgs[2]));
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}